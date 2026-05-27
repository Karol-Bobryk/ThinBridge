
// code ( kot )
//        /|_ /|
//     \ / _  _ \ /
//     -<    ^   >-
//     /  \    /  \
//        /    \
//       /      |
//       |      |
//  |\__/        \
//   \______\_\\__\
/
#include "ArgumentParser.h"
#include "Car.h"
#include "Globals.h"
#include "ThreadList.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

Globals globals = globals_init;

pthread_mutex_t bridge_access;
pthread_cond_t bridge_cond;
bool bridge_busy;

void *routine(void *arg) {
  if (pthread_mutex_lock(&bridge_access) != 0) {
    perror("error getting mutex access");
    return NULL;
  }

  while (bridge_busy) {
    pthread_cond_wait(&bridge_cond, &bridge_access);
  }

  bridge_busy = true;

  Car *car = ((Car *)arg);

  car_print_state(car);

  if (car->is_going_left) {
    globals.city_a_arrived_cars_count++;
    globals.city_b_cars_left--;
  } else {
    globals.city_b_arrived_cars_count++;
    globals.city_a_cars_left--;
  }

  if (pthread_mutex_unlock(&bridge_access) != 0) {
    perror("error freeing mutex access");
    return NULL;
  }

  sleep(1);

  if (pthread_mutex_lock(&bridge_access) != 0) {
    perror("error getting mutex access");
    return NULL;
  }

  bridge_busy = false;

  pthread_cond_signal(&bridge_cond);

  if (pthread_mutex_unlock(&bridge_access) != 0) {
    perror("error freeing mutex access");
    return NULL;
  }

  return NULL;
}

int main(int argc, char **argv) {

  if (pthread_mutex_init(&bridge_access, NULL) != 0) {
    perror("error initializing mutex");
    return EXIT_FAILURE;
  }
  if (pthread_cond_init(&bridge_cond, NULL) != 0) {
    perror("error initializing conditional variable");
    return EXIT_FAILURE;
  }

  arg_parser_init(argc, argv);

  unsigned int seed = time(0);

  globals_divide_cars_randomly(seed);

  car_print_state(NULL);

  Car *city_a_cars = malloc(globals.city_a_cars_count * sizeof(Car));
  Car *city_b_cars = malloc(globals.city_b_cars_count * sizeof(Car));

  if (city_a_cars == NULL || city_b_cars == NULL) {
    perror("error initializing car structs");
    return EXIT_FAILURE;
  }

  car_populate_list(city_a_cars, globals.city_a_cars_count, false, 0);

  car_populate_list(city_b_cars, globals.city_b_cars_count, true,
                    globals.city_a_cars_count);

  pthread_t *city_a_car_threads =
      malloc(globals.city_a_cars_count * sizeof(pthread_t));
  pthread_t *city_b_car_threads =
      malloc(globals.city_b_cars_count * sizeof(pthread_t));

  if (city_a_car_threads == NULL || city_b_car_threads == NULL) {
    perror("error initializing threads");
    return EXIT_FAILURE;
  }

  if (create_thread_list(city_a_car_threads, globals.city_a_cars_count, routine,
                         city_a_cars) != 0) { // TODO: add passing args
                                              //
    perror("Failed to alloc thread list A");
    return EXIT_FAILURE;
  }

  if (create_thread_list(city_b_car_threads, globals.city_b_cars_count, routine,
                         city_b_cars) != 0) {
    perror("Failed to alloc thread list B");
    return EXIT_FAILURE;
  }

  // TODO: add waiting for all threads
  for (int i = 0; i < globals.city_a_cars_count; ++i) {
    if (pthread_join(city_a_car_threads[i], NULL) != 0) {
      perror("Failed to join a threads");
      return EXIT_FAILURE;
    }
  }

  for (int i = 0; i < globals.city_b_cars_count; ++i) {
    if (pthread_join(city_b_car_threads[i], NULL) != 0) {
      perror("Failed to join b threads");
      return EXIT_FAILURE;
    }
  }

  car_print_state(NULL);

  free(city_a_cars);
  free(city_b_cars);

  pthread_mutex_destroy(&bridge_access); // TODO: add checking
  pthread_cond_destroy(&bridge_cond);    // do we need to do anything here?
  free_thread_list(city_a_car_threads, globals.city_a_cars_count);
  free_thread_list(city_b_car_threads, globals.city_b_cars_count);

  return EXIT_SUCCESS;
}

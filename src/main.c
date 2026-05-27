
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
#define _POSIX_C_SOURCE 199309L
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

void *routine(void *arg) {
  Car *car = ((Car *)arg);

  struct timespec ts;
  while (1) {
    ts.tv_sec = 0;
    ts.tv_nsec = rand() % 50000000;

    if (pthread_mutex_lock(&bridge_access) != 0) {
      perror("error getting mutex access");
      return NULL;
    }

    car_print_state(car);

    if (car->is_going_left) {
      globals.city_a_arrived_cars_count++;
      globals.city_b_cars_left--;
    } else {
      globals.city_b_arrived_cars_count++;
      globals.city_a_cars_left--;
    }

    nanosleep(&ts, NULL);

    car_print_state(NULL);

    car_turn_around(car);

    car_print_state(NULL);

    if (pthread_mutex_unlock(&bridge_access) != 0) {
      perror("error freeing mutex access");
      return NULL;
    }

    nanosleep(&ts, NULL);
  }
  return NULL;
}

int main(int argc, char **argv) {

  if (pthread_mutex_init(&bridge_access, NULL) != 0) {
    perror("error initializing mutex");
    return EXIT_FAILURE;
  }

  arg_parser_init(argc, argv);

  unsigned int seed = time(0);

  globals_divide_cars_randomly(seed);

  car_print_state(NULL);

  Car *city_cars = malloc(globals.number_of_cars * sizeof(Car));

  if (city_cars == NULL) {
    perror("error initializing car struct");
    return EXIT_FAILURE;
  }

  car_populate_list(city_cars, globals.city_a_cars_count, false, 0);

  car_populate_list(city_cars + globals.city_a_cars_count,
                    globals.city_b_cars_count, true, 0);

  pthread_t *city_car_threads =
      malloc(globals.number_of_cars * sizeof(pthread_t));

  if (city_car_threads == NULL) {
    perror("error initializing threads");
    return EXIT_FAILURE;
  }

  if (create_thread_list(city_car_threads, globals.number_of_cars, routine,
                         city_cars) != 0) {
    perror("Failed to alloc thread list");
    return EXIT_FAILURE;
  }

  for (int i = 0; i < globals.number_of_cars; ++i) {
    if (pthread_join(city_car_threads[i], NULL) != 0) {
      perror("Failed to join a threads");
      return EXIT_FAILURE;
    }
  }

  car_print_state(NULL);

  free(city_cars);

  pthread_mutex_destroy(&bridge_access);
  free_thread_list(city_car_threads, globals.number_of_cars);

  return EXIT_SUCCESS;
}

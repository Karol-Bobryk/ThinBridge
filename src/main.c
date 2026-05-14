
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
#include "Globals.h"
#include "ThreadList.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Globals globals = globals_init;

size_t city_a_cars_count = 0;
size_t city_b_cars_count = 0;
size_t city_a_arrived_cars_count = 0;
size_t city_b_arrived_cars_count = 0;

pthread_mutex_t bridge_access;
sem_t is_traffic_finished;

#define DIRECTION_ARROW_LEFT "<<"
#define DIRECTION_ARROW_RIGHT ">>"

void *routine(void *arg) {
  if (pthread_mutex_lock(&bridge_access) != 0) {
    perror("error getting mutex access");
    return NULL;
  }

  // TODO: change default values

  // 0 - car is going RIGHT >>
  // 1 - car is going LEFT <<

  bool is_going_left = *((bool *)arg);

  pthread_t car_id = pthread_self();

  if (is_going_left) {
    printf("A-%zu %zu >>> [%s %zu %s] <<< %zu %zu-B ",
           city_a_arrived_cars_count, city_a_cars_count, DIRECTION_ARROW_LEFT,
           car_id, DIRECTION_ARROW_LEFT, city_b_cars_count,
           city_b_arrived_cars_count);
    city_a_arrived_cars_count++;
  } else {
    printf("A-%zu %zu >>> [%s %zu %s] <<< %zu %zu-B ",
           city_a_arrived_cars_count, city_a_cars_count, DIRECTION_ARROW_RIGHT,
           car_id, DIRECTION_ARROW_RIGHT, city_b_cars_count,
           city_b_arrived_cars_count);
    city_b_arrived_cars_count++;
  }

  printf("\n");

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

  if (sem_init(&is_traffic_finished, 0, 1) != 0) {
    perror("error initializing semaphore");
    return EXIT_FAILURE;
  }

  arg_parser_init(argc, argv);

  unsigned int seed = time(0);
  srand(seed);

  city_a_cars_count = globals.number_of_cars;
  city_b_cars_count = rand() % globals.number_of_cars;
  city_a_cars_count -= city_b_cars_count;

  pthread_t *city_a_cars =
      malloc(city_a_cars_count * sizeof(pthread_t)); // TODO: NULLcheck

  pthread_t *city_b_cars =
      malloc(city_b_cars_count * sizeof(pthread_t)); // TODO: NULLcheck

  bool is_going_left = true;
  bool is_going_right = false;

  if (create_thread_list(city_a_cars, city_a_cars_count, routine,
                         &is_going_right) != 0) { // TODO: add passing args
    perror("Failed to alloc thread list A");
    return EXIT_FAILURE;
  }

  if (create_thread_list(city_b_cars, city_b_cars_count, routine,
                         &is_going_left) != 0) {

    perror("Failed to alloc thread list B");
    return EXIT_FAILURE;
  } // TODO: add waiting for all threads

  for (int i = 0; i < city_a_cars_count; ++i) {
    if (pthread_join(city_a_cars[i], NULL) != 0) {
      perror("Failed to join a threads");
      return EXIT_FAILURE;
    }
  }

  for (int i = 0; i < city_b_cars_count; ++i) {
    if (pthread_join(city_b_cars[i], NULL) != 0) {
      perror("Failed to join b threads");
      return EXIT_FAILURE;
    }
  }

  pthread_mutex_destroy(&bridge_access); // TODO: add checking
  sem_destroy(&is_traffic_finished);     // TODO: add checking
  free_thread_list(city_a_cars, city_a_cars_count);
  free_thread_list(city_b_cars, city_b_cars_count);

  return EXIT_SUCCESS;
}

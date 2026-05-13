
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
#include <stdio.h>
#include <stdlib.h>

Globals globals = globals_init;

int main(int argc, char **argv) {

  arg_parser_init(argc, argv);

  unsigned int seed = time(0);
  srand(seed);

  size_t city_a_cars_count = globals.number_of_cars;
  size_t city_b_cars_count = rand() % globals.number_of_cars;
  city_a_cars_count -= city_b_cars_count;

  pthread_t *city_a_cars = malloc(sizeof(pthread_t) * city_a_cars_count);

  pthread_t *city_b_cars = malloc(sizeof(pthread_t) * city_b_cars_count);

  if (create_thread_list(&city_a_cars, city_a_cars_count) != 0) {
    perror("Failed to alloc thread list A");
    return 1;
  }

  if (create_thread_list(&city_b_cars, city_b_cars_count) != 0) {
    perror("Failed to alloc thread list B");
    return 1;
  }

  free_thread_list(&city_a_cars, city_a_cars_count);
  free_thread_list(&city_b_cars, city_b_cars_count);

  return EXIT_SUCCESS;
}

#ifndef GLOBALS_H
#define GLOBALS_H
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define GLOBALS_DEFAULT_NUMBER_OF_CARS 1
#define GLOBALS_DEFAULT_CARS_COUNT 0

#define globals_init                                                           \
  {.number_of_cars = GLOBALS_DEFAULT_NUMBER_OF_CARS,                           \
   .city_a_cars_count = GLOBALS_DEFAULT_CARS_COUNT,                            \
   .city_b_cars_count = GLOBALS_DEFAULT_CARS_COUNT,                            \
   .city_a_arrived_cars_count = GLOBALS_DEFAULT_CARS_COUNT,                    \
   .city_b_arrived_cars_count = GLOBALS_DEFAULT_CARS_COUNT,                    \
   .city_a_cars_left = GLOBALS_DEFAULT_CARS_COUNT,                             \
   .city_b_cars_left = GLOBALS_DEFAULT_CARS_COUNT}

#define globals_divide_cars_randomly(seed)                                     \
  {                                                                            \
    srand(seed);                                                               \
    globals.city_a_cars_count = globals.number_of_cars;                        \
    globals.city_b_cars_count = rand() % globals.number_of_cars;               \
    globals.city_a_cars_count -= globals.city_b_cars_count;                    \
    globals.city_a_cars_left = globals.city_a_cars_count;                      \
    globals.city_b_cars_left = globals.city_b_cars_count;                      \
  }

typedef struct {
  size_t number_of_cars;
  size_t city_a_cars_count;
  size_t city_b_cars_count;

  size_t city_a_arrived_cars_count;
  size_t city_b_arrived_cars_count;

  size_t city_a_cars_left;
  size_t city_b_cars_left;

} Globals;

extern Globals globals;
#endif

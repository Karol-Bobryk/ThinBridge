#ifndef GLOBALS_H
#define GLOBALS_H
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define GLOBALS_DEFAULT_NUMBER_OF_CARS 1

#define globals_init {.number_of_cars = GLOBALS_DEFAULT_NUMBER_OF_CARS}

typedef struct {
  size_t number_of_cars;
} Globals;

extern Globals globals;
#endif

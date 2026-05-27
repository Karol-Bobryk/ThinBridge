#ifndef CAR_H
#define CAR_H

#include <stdbool.h>
#include <stdio.h>

typedef struct {
  int id;
  bool is_going_left;
} Car;

void car_print_state(Car *car);

int car_populate_list(Car *list, size_t list_length, bool is_going_left,
                      size_t statring_index);

void car_turn_around(Car *car);

#endif

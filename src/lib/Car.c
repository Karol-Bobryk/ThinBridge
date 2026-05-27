#include "Globals.h"
#include <Car.h>

void car_print_state(Car *car) {

  printf("A-%zu %zu >>> ", globals.city_a_arrived_cars_count,
         globals.city_a_cars_left);

  if (car == NULL)
    printf("[==   ==]");
  else if (car->is_going_left)
    printf("[<< %d <<]", car->id);
  else
    printf("[>> %d >>]", car->id);

  printf(" <<< %zu %zu-B\n", globals.city_b_cars_left,
         globals.city_b_arrived_cars_count);
}

int car_populate_list(Car *list, size_t list_length, bool is_going_left,
                      size_t statring_index) {
  if (list == NULL) {
    perror("car list cannot be null");
    return 1;
  }

  for (size_t i = 0; i < list_length; ++i) {
    list[i].is_going_left = is_going_left;
    list[i].id = statring_index + i;
  }

  return 0;
}

void car_turn_around(Car *car) {

  if (car->is_going_left) {
    globals.city_a_cars_left++;
    globals.city_a_arrived_cars_count--;
  } else {
    globals.city_b_cars_left++;
    globals.city_b_arrived_cars_count--;
  }

  car->is_going_left = !car->is_going_left;
}

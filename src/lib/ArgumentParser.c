
#include "ArgumentParser.h"
#include "Globals.h"
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const char *OPTSTRING = "N:";

#define OPT_NUMBER_OF_CARS 'N'

void arg_parser_init(int argc, char **argv) {
  int current_option;
  while ((current_option = getopt(argc, argv, OPTSTRING)) != -1) {
    if (arg_parser_process_arg(current_option) != 0)
      goto parser_init_error;
  }

  return;

parser_init_error:
  perror("Invalid option or argument");
  exit(EXIT_FAILURE);
}

int arg_parser_process_arg(int opt) {

  switch (opt) {
  case OPT_NUMBER_OF_CARS: {
    globals.number_of_cars = atoi(optarg);

    if (globals.number_of_cars == 0)
      return 1;

    break;
  }

  default: /*fallthrough*/
  case '?':
    return 1;
  }

  return 0;
}

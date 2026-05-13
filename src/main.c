
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
#include <pthread.h>
#include <stdlib.h>

Globals globals = globals_init;

int main(int argc, char **argv) {

  arg_parser_init(argc, argv);
  printf("\n%zu\n", globals.number_of_cars);

  return EXIT_SUCCESS;
}

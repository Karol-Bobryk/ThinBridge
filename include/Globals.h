#ifndef GLOBALS_H
#define GLOBALS_H
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define GLOBALS_DEFAULT_SLEEP_TIME 5 * 60
#define GLOBALS_DEFAULT_FILE_SIZE_TRESHOLD 4096
#define GLOBALS_DEFAULT_RECURSIVE_SCANNING false

#define globals_init                                                           \
  {.destination_path = NULL,                                                   \
   .source_path = NULL,                                                        \
   .file_size_treshold = GLOBALS_DEFAULT_FILE_SIZE_TRESHOLD,                   \
   .recursive_scanning = GLOBALS_DEFAULT_RECURSIVE_SCANNING,                   \
   .sleep_time = GLOBALS_DEFAULT_SLEEP_TIME}

#define PATH_TYPE_SRC globals.source_path
#define PATH_TYPE_DST globals.destination_path

typedef struct {
  size_t sleep_time;
  size_t file_size_treshold;

  char *source_path;
  char *destination_path;

  bool recursive_scanning;
} Globals;

extern Globals globals;
#endif

#include "ThreadList.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int create_thread_list(pthread_t *thread_list, size_t thread_count,
                       void *(*routine)(void *), bool *is_going_left) {

  for (size_t i = 0; i < thread_count; ++i) {

    if (pthread_create(&(thread_list[i]), NULL, routine, is_going_left) != 0) {
      return 1;
    }
  }

  return 0;
}

void free_thread_list(pthread_t *thread_list, size_t thread_count) {
  free(thread_list);
}

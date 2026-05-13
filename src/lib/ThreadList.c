#include "ThreadList.h"
#include <pthread.h>
#include <stdlib.h>

void *thread_func(void *a) { return a; } // TODO: delete

int create_thread_list(pthread_t **thread_list, size_t thread_count) {

  for (size_t i = 0; i < thread_count; ++i) {
    if (pthread_create(thread_list[i], NULL, thread_func, NULL) != 0)
      return 1;
  }
  return 0;
}

void free_thread_list(pthread_t **thread_list, size_t thread_count) {

  for (size_t i = 0; i < thread_count; ++i) {
    // TODO: delete threads
  }
  free(thread_list);
}

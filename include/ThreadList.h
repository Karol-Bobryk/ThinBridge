#ifndef THREAD_LIST_H
#define THREAD_LIST_H

#include <bits/pthreadtypes.h>
#include <stdbool.h>
#include <stddef.h>

int create_thread_list(pthread_t *thread_list, size_t thread_count,
                       void *(*routine)(void *), bool *is_going_left);
void free_thread_list(pthread_t *thread_list, size_t thread_count);
#endif

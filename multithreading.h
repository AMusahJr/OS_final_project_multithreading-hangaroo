// multithreading.h

#ifndef MULTITHREADING_H
#define MULTITHREADING_H

#include <pthread.h>

// Function prototypes for multithreading library
int create_thread(pthread_t *thread, void *(*start_routine)(void *), void *arg);
int join_thread(pthread_t thread, void **retval);
void initialize_mutex(pthread_mutex_t *mutex);
void lock_mutex(pthread_mutex_t *mutex);
void unlock_mutex(pthread_mutex_t *mutex);
void destroy_mutex(pthread_mutex_t *mutex);
void initialize_cond(pthread_cond_t *cond);
void wait_cond(pthread_cond_t *cond, pthread_mutex_t *mutex);
void signal_cond(pthread_cond_t *cond);
void broadcast_cond(pthread_cond_t *cond);
void destroy_cond(pthread_cond_t *cond);

#endif

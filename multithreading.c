// multithreading.c

#include "multithreading.h"
#include "hangaroo.h"

// Function implementations for multithreading library
int create_thread(pthread_t *thread, void *(*start_routine)(void *), void *arg) {
    return pthread_create(thread, NULL, start_routine, arg);
}

int join_thread(pthread_t thread, void **retval) {
    return pthread_join(thread, retval);
}

void initialize_mutex(pthread_mutex_t *mutex) {
    pthread_mutex_init(mutex, NULL);
}

void lock_mutex(pthread_mutex_t *mutex) {
    pthread_mutex_lock(mutex);
}

void unlock_mutex(pthread_mutex_t *mutex) {
    pthread_mutex_unlock(mutex);
}

void destroy_mutex(pthread_mutex_t *mutex) {
    pthread_mutex_destroy(mutex);
}

void initialize_cond(pthread_cond_t *cond) {
    pthread_cond_init(cond, NULL);
}

void wait_cond(pthread_cond_t *cond, pthread_mutex_t *mutex) {
    pthread_cond_wait(cond, mutex);
}

void signal_cond(pthread_cond_t *cond) {
    pthread_cond_signal(cond);
}

void broadcast_cond(pthread_cond_t *cond) {
    pthread_cond_broadcast(cond);
}

void destroy_cond(pthread_cond_t *cond) {
    pthread_cond_destroy(cond);
}

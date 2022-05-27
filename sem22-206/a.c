#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <malloc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void* task(void * ptr) {
    printf("Task %lu\n", pthread_self());
    return 0;
}

int main(int argc, char** args) { // args[1] - amount
    printf("Main %lu\n", pthread_self());
    int n = atoi(args[1]);
    pthread_t* threads = calloc(n, sizeof(*threads));

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, sysconf(_SC_THREAD_STACK_MIN));
    pthread_attr_setguardsize(&attr, 0);

    for (int i = 0; i < n; ++i) {
        pthread_create(threads + i, &attr, task, NULL);  // &threads[i]
    }

    pthread_attr_destroy(&attr);


    for (int i = 0; i < n; ++i) {
        pthread_join(threads[i], NULL);
    }

    free(threads);
}

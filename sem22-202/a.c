#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


void* work(void* val) {
    printf("Work %ld\n", pthread_self());
    sleep(10);
    return NULL;
}


int main() {
    printf("Main %ld\n", pthread_self());
    pthread_t thread;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);

    pthread_create(&thread, &attr, work, NULL);
    pthread_attr_destroy(&attr);

    sleep(20);
    pthread_join(thread, NULL);
}

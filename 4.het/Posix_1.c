#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/*
Main thread runs for 8 secons.
Child thread for 4 seconds.
gcc Posix_2.c -pthread -o Posix_2.exe
*/
void main_thread();

void *child_thread(void *vargp);

int main() {
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, child_thread, NULL);
    main_thread();
    pthread_join(thread_id, NULL);
    printf("Child thread killed.\n");
    return (0);
}

void main_thread() {
    time_t start_time = time(NULL);
    while (time(NULL) - start_time < 8) {
        printf("Main  thread runtime: %d s\n", time(NULL) - start_time);
        sleep(1);
    }
}

void *child_thread(void *vargp) {
    time_t start_time = time(NULL);
    while (time(NULL) - start_time < 4) {
        printf("Child thread runtime: %d s\n", time(NULL) - start_time);
        sleep(1);
    }
}

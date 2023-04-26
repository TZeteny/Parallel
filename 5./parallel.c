/*
Calculates the sum of an array in threads.
You give the number of threads.
If the length of the array isn't divisible by
the number of threads, it gives the extra numbers to the last thread.
gcc name.c -pthread -o name.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct data {
    int thread_number;
    int split;
    //extra numbers, if length isn't divisible by threads
    int extra;
} Data;

int arr[10];
long long int sum = 0;

void* part_sum(void* arg);

int main() {
    int length = 1000;
    //number of threads
    int threads;
    printf("How many threads would you like: ");
    scanf("%d", &threads);
    //length of the split parts
    int split = length / threads;
    printf("Split part length: %d\n", split);
    int i;
    //extra numbers, if length isn't divisible by threads
    int extra;
    printf("the array: ");
    for (i = 0; i < length; i++) {
        arr[i] = i + 1;
        printf("%d, ", arr[i]);
    }
    printf("\n");
    //create a Data array the size of number of threads
    Data data_arr[threads];
    //thread number
    int thread_no;
    pthread_t id[threads];
    //for measuring runtime
    clock_t start, end;
    double cpu_time_taken;

    //start the clock
    start = clock();

    for (thread_no = 0; thread_no < threads - 1; thread_no++) {
        printf("Creating thread #%d\n", thread_no);
        data_arr[thread_no].thread_number = thread_no;
        data_arr[thread_no].split = split;
        data_arr[thread_no].extra = 0;
        pthread_create(&id[thread_no], NULL, part_sum, &data_arr[thread_no]);
    }
    //if length isn't divisible by threads
    if ( (extra = length % threads) != 0) {
        printf("Extra: %d\n", extra);
        data_arr[thread_no].extra = extra;
    }
    else {
        data_arr[thread_no].extra = 0;
    }
    printf("Creating thread #%d\n", thread_no);
        data_arr[thread_no].thread_number = thread_no;
        data_arr[thread_no].split = split;
        pthread_create(&id[thread_no], NULL, part_sum, &data_arr[thread_no]);

    for (i = 0; i < threads; i++) {
        pthread_join(id[i], NULL);
    }

    end = clock();
    cpu_time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nSum: %lld\n", sum);
    printf("\nTime taken: %lf s\n", cpu_time_taken);

    return 0;
}

void* part_sum(void* arg) {
    Data* current_thread_data = (Data*) arg;

    int start = 0 + current_thread_data->thread_number * current_thread_data->split;
    int end = -1 + (current_thread_data->thread_number + 1) * current_thread_data->split + current_thread_data->extra;
    printf("Thread #%d start: %d , end: %d\n",current_thread_data->thread_number, start, end);
    int i;

    int current_thread_sum = 0;
    for (i = start; i <= end; i++) {
        current_thread_sum += arr[i];
    }
    printf("Thread #%d sum = %d\n", current_thread_data->thread_number, current_thread_sum);

    sum += current_thread_sum;

    return NULL;
}

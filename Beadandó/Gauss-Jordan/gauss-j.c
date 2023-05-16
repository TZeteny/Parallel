/*
all:
	gcc gauss-j.c -pthread -o gauss-j.exe
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct data {
    int threadNum;
    int n;
    double* matrix;
} Data;

void fill_matrix();
void print_matrix();
void gauss_jordan();
void copy_matrix(); //Copy matrix A to B
void* gj_pt();

//int wait = 0;
pthread_mutex_t mutex;

int main() {
    int n; //Side of the square matrix
    printf("Square matrix size (n*n): ");
    scanf("%d", &n);
    int threads = n - 1;
    int max; //Max matrix value
    printf("Matrix max: ");
    scanf("%d", &max);
    double start[n * n]; //The starting matrix. Do not modify!
    double aux[n * n]; //Auxillary matrix that can be modified freely
    //threads
    int threadNum; //Number of the thread
    pthread_t id[threads]; //IDs for the threads
    Data data[threads]; //create a Data array the size of number of threads
    clock_t t; //for measuring runtime
    double runtimeA;
    double runtimeB;

    fill_matrix(start, n, max);
    printf("The starting matrix:\n");
    //print_matrix(start, n);
    copy_matrix(start, aux, n);

    //Without threading
    t = clock(); //start measuring
    gauss_jordan(aux, n);
    printf("The matrix after unthreaded G-J:\n");
    //print_matrix(aux, n);
    t = clock() - t; //stop clock
    runtimeA = ((double)t)/CLOCKS_PER_SEC;

    //With threads
    t = clock(); //start measuring
    copy_matrix(start, aux, n);
    pthread_mutex_init(&mutex, NULL); //for making threads wait

    for (threadNum = 0; threadNum < threads; threadNum++) {
        data[threadNum].threadNum = threadNum;
        data[threadNum].n = n;
        data[threadNum].matrix = aux;
        pthread_create(&id[threadNum], NULL, gj_pt, &data[threadNum]);
    }

    for (int i = 0; i < threads; i++) {
        pthread_join(id[i], NULL);
    }
    pthread_mutex_destroy(&mutex); //destroy mutex

    printf("Matrix after threaded G-J:\n");
    //print_matrix(aux, n);

    t = clock() - t; //stop clock
    runtimeB = ((double)t)/CLOCKS_PER_SEC;

    printf("\nRuntime without pthread: %lfs.\n", runtimeA);
    printf("Runtime with pthread: %lfs.\n", runtimeB);

    return 0;
}

void fill_matrix(double matrix[], int n, int max) {
    int i, j;
    //int k = 1; // for test values 1 to (n + 1)
    /*
    3x3 test matrix should be:
    1 | 2 | 3
    4 | 5 | 6
    7 | 8 | 9

    The result should be:
    1 | 0 | -1
    0 | 1 | 2
    0 | 0 | 0
    */

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            matrix[i * n + j] = (double)(rand()%max);
            //Whole nmubers for easier manual checking
            /*matrix[i * n + j] = rand()%max;*/
            //for testing with 1 to (n + 1)
            /*matrix[i * n + j] = k;
            k++;*/
        }
    }

}

void print_matrix(double matrix[], int n) {
    int i, j;

    for (i = 0; i < n; i++) {
        printf("|");
        for (j = 0; j < n; j++) {
            printf(" %lf |", matrix[i * n + j]);
        }
        printf("\n");
    }
    printf("\n");

}

void copy_matrix(double mA[], double mB[], int n) {
    int i;

    for(i = 0; i < (n * n); i++) {
        mB[i] = mA[i];
    }
}

void gauss_jordan(double matrix[], int n) {
    int i, j, k;
    double temp[n * n];
    copy_matrix(matrix, temp, n);
    double pivot;
    double r, c; //Numbers used for calculations from the pivot's row and column

    for (i = 0; i < (n - 1); i++) {
        pivot = matrix[i * n + i];
        //Divide the pivot's row with pivot
        for (j = i; j < n; j++) {
            temp[i* n + j] /= matrix[i * n + i];
        }
        //Null the other elements in the pivot's column
        for (j = 0; j < n; j++) {
            temp[j * n + i] = 0;
        }
        temp[i * n + i] = 1;
        //Calculate the other values
        //J goes through the columns to the pivot's right
        for (j = (i + 1); j < n; j++) {
            //K goes through the rows
            for (k = 0; k < n; k++) {
                r = matrix[k * n + i];
                c = matrix[i * n + j];
                if (k != i) { //So the pivot's row isn't affected
                    temp[k * n + j] -= ((r * c) / pivot);
                }
            }
        }
        copy_matrix(temp, matrix, n);
        /*printf("The matrix after step %d:\n", i + 1);
        print_matrix(matrix, n);*/
    }

}

void* gj_pt(void* arg) {
    Data* thread_data = (Data*) arg;
    int i = thread_data->threadNum, j, k;
    double temp[thread_data->n * thread_data->n];
    copy_matrix(thread_data->matrix, temp, thread_data->n);
    double pivot = thread_data->matrix[i * thread_data->n + i];
    double r, c; //Numbers used for calculations from the pivot's row and column

    //Divide the pivot's row with pivot
    for (j = i; j < thread_data->n; j++) {
        temp[i* thread_data->n + j] /= thread_data->matrix[i * thread_data->n + i];
    }
    //Null the other elements in the pivot's column
    for (j = 0; j < thread_data->n; j++) {
        temp[j * thread_data->n + i] = 0;
    }
    temp[i * thread_data->n + i] = 1;
    //Calculate the other values
    //J goes through the columns to the pivot's right
    for (j = (i + 1); j < thread_data->n; j++) {
        //K goes through the rows
        for (k = 0; k < thread_data->n; k++) {
            r = thread_data->matrix[k * thread_data->n + i];
            c = thread_data->matrix[i * thread_data->n + j];
            if (k != i) { //So the pivot's row isn't affected
                temp[k * thread_data->n + j] -= ((r * c) / pivot);
            }
        }
    }

    pthread_mutex_lock(&mutex); //Making the other threads wait.
    copy_matrix(temp, thread_data->matrix, thread_data->n);
    //printf("The matrix after thread #%d:\n", thread_data->threadNum);
    //print_matrix(thread_data->matrix, thread_data->n);
    pthread_mutex_unlock(&mutex); //Letting them continue

}














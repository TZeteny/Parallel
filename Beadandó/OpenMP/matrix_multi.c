/*
Matrix multiplication with N*N sized matrices
Makefile: gcc matrix_multi.c -fopenmp -o -matrix.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <string.h>

void fill_matrix();
void print_matrix();
//To set the base state of the result matrix
void fill_null_matrix();
//Sequential and OpenMP multiplication
void multiply_matrices();
void multiply_omp();

int main() {
    srand(time(NULL));
    int n; //Matrix size
    printf("Square matrix size (n*n): ");
    scanf("%d", &n);
    int threads; //Number of threads
    printf("How many threads: ");
    scanf("%d", &threads);
    int max; //matrix value max
    printf("Matrix max: ");
    scanf("%d", &max);
    clock_t t; //for measuring runtime
    double runtime;

    //Matrices A, B and the result
    long double mA[n*n];
    long double mB[n*n];
    long double result[n*n];

    fill_matrix(mA, n, max);
    printf("Matrix A:\n");
    //print_matrix(mA, n);

    fill_matrix(mB, n, max);
    printf("Matrix B:\n");
    //print_matrix(mB, n);

    t = clock(); //start measuring
    multiply_matrices(mA, mB, result, n);
    printf("Result sequential:\n");
    //print_matrix(result, n);
    t = clock() - t; //stop clock
    runtime = ((double)t)/CLOCKS_PER_SEC;
    printf("Sequential runtime: %lfs\n", runtime);

    t = clock(); //start measuring
    multiply_omp(mA, mB, result, n, threads);
    printf("Result matrix OMP:\n");
    //print_matrix(result, n);
    t = clock() - t; //stop clock
    runtime = ((double)t)/CLOCKS_PER_SEC;
    printf("OMP runtime: %lfs\n", runtime);

    return 0;
}

void fill_matrix(long double matrix[], int n, int max) {
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            matrix[i * n + j] = (long double)(rand()%max);
            //Whole nmubers for easier manual checking
            //matrix[i * n + j] = rand()%max;
        }
    }

}

void fill_null_matrix(long double matrix[], int n) {
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            matrix[i * n + j] = 0;
        }
    }

}

void print_matrix(long double matrix[], int n) {
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

void multiply_matrices(long double mA[], long double mB[], long double result[], int n) {
    int i, j, k;
    fill_null_matrix(result, n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            //K goes through A's rows and B's columns
            for (k = 0; k < n; k++) {
                result[i * n + j] += mA[i * n + k] * mB[k * n + j];
            }
        }
    }

}

void multiply_omp(long double mA[], long double mB[], long double result[], int n, int threads) {
    fill_null_matrix(result, n);
    omp_set_num_threads(threads);

    #pragma omp parallel shared(mA, mB, result)
    {
        int threadNum = omp_get_thread_num();

        int i, j, k;

        //i starting with threadNum breaks up the operations between thread
        for (i = threadNum; i < n; i += threads) {
            for (j = 0; j < n; j++) {
                //K goes through A's rows and B's columns
                for (k = 0; k < n; k++) {
                    result[i * n + j] += mA[i * n + k] * mB[k * n + j];
                }
            }
        }
    }

}

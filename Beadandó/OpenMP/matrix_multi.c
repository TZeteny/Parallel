/*
Matrix multiplication with N*N sized matrices
Makefile: gcc matrix_multi.c -fopenmp -o -matrix.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <string.h>

#define N 3 //Size of the matrices (N*N)

void fill_matrix();
void print_matrix();
//To set the base state of the result matrix
void fill_null();
//Sequential and OpenMP multiplication
void multiply_matrices();
void multiply_omp();

int main() {
    srand(time(NULL));
    int threads; //Number of threads
    printf("How many threads: ");
    scanf("%d", &threads);
    //matrix value max:
    int max;
    printf("Matrix max: ");
    scanf("%d", &max);
    //Matrices A, B and the result
    double mA[N][N];
    double mB[N][N];
    double result[N][N];

    fill_matrix(mA, max);
    printf("Matrix A:\n");
    print_matrix(mA);

    fill_matrix(mB, max);
    printf("Matrix B:\n");
    print_matrix(mB);

    multiply_matrices(mA, mB, result);
    printf("Result matrix sequential:\n");
    print_matrix(result);

    multiply_omp(mA, mB, result, threads);
    printf("Result matrix OMP:\n");
    print_matrix(result);

    return 0;
}

void fill_matrix(double matrix[N][N], int max) {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
           matrix[i][j] = (double)(rand()%max);
           /*matrix[i][j] = rand()%max;
           //Whole nmubers for easier manual checking
           */
        }
    }
}

void fill_null(double matrix[N][N]) {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
           matrix[i][j] = 0.0;
        }
    }
}

void print_matrix(double matrix[N][N]) {
    int i, j;

    for (i = 0; i < N; i++) {
        printf("|");
        for (j = 0; j < N; j++) {
           printf(" %lf |", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void multiply_matrices(double mA[N][N], double mB[N][N], double result[N][N]) {
    int i, j, k;

    fill_null(result);

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            //K goes through A's rows and B's columns
            for (k = 0; k < N; k++) {
                result[i][j] += mA[i][k] * mB[k][j];
            }
        }
    }

}

void multiply_omp(double mA[N][N], double mB[N][N], double result[N][N], int threads) {
    fill_null(result);
    omp_set_num_threads(threads);

    #pragma omp parallel shared(mA, mB, result)
    {
        int threadNum = omp_get_thread_num();

        int i, j, k;

        //i starting with threadNum breaks up the operations between thread
        for (i = threadNum; i < N; i += threads) {
            for (j = 0; j < N; j++) {
                //K goes through A's rows and B's columns
                for (k = 0; k < N; k++) {
                    result[i][j] += mA[i][k] * mB[k][j];
                }
            }
        }
    }
}

//Calculate the product of an array's elements in a vareity of ways.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void fill_array();
double calc_par();
double calc_red();

int main() {
    int length = 10;
    double arr[length];
    fill_array(arr, length, 1, 100);
    int i;
    double prod = 1;
    double part_prod = 1;

    //sequencial
    for (i = 0; i < length; i++) {
        prod *= arr[i];
    }
    printf("Sequencial product: %lf\n", prod);

    //in parallel openmp threads
    prod = calc_par(arr, length);
    printf("OpenMP product: %lf\n", prod);

    //using reduction
    prod = calc_red(arr, length);
    printf("Reduction product: %lf\n", prod);


    return 0;
}

void fill_array(double* arr, int length, int min, int max) {
    srand(time(NULL));
    int i;

    for (i = 0; i < length; i++) {
        arr[i] = (double)(rand()%(max - min + 1) + min);
    }
}

double calc_par(double* arr, int length) {
    int i;
    double prod = 1, part_prod = 1;

    #pragma omp parallel for private(part_prod) shared (prod)
    {
            for (i = 0; i < length; i++) {
                part_prod *= arr[i];
            }

        #pragma omp critical
        {
            prod *= part_prod;
        }
    }

    return prod;
}

double calc_red(double* arr, int length) {
    int i;
    double prod = 1, part_prod = 1;

    #pragma omp parallel for reduction(*:prod) private(part_prod)
    {
            for (i = 0; i < length; i++) {
                part_prod *= arr[i];
            }
            prod *= part_prod;
    }

    return prod;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_array();
void unique();

int main() {
    int size;
    printf("array size: ");
    scanf("%d", &size);
    int array[size];
    clock_t t;
    double time_taken;

    //Time before execution
    t = clock();
    generate_array(array, size);

    //Time after execution minus time before exection
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("It took %lf seconds to generate an array with %d elements.\n", time_taken, size);

    /*for (int i = 0; i < size; i++) {
        printf("%d, ", array[i]);
    }
    printf("\n");*/

    unique(array, size);

    return 0;
}

void generate_array(int* array, int size) {
    int i, j;
    srand(time(NULL));
    int different;
    //Dupe will be either 0 or 1. 50% chance of duplication.
    int dupe = rand()%2;
    //printf("dupe = %d\n", dupe);

    for(i = 0; i < size; i++) {
        //Generate numbers untill it is a unique number.
        do {
            different = 1;
            array[i] = rand();
            for(j = 0; j < i; j++) {
                if(array[j] == array[i]) {
                    different = 0;
                }
            }
        }while(!different);
    }

    //There will be 2 identical numbers in the array.
    if(dupe == 1) {
        array[size - 1] = array[size - 2];
    }

}

/*
    Initialising i and j takes a set amount of time, C1.
    Performing the check in the if statement takes a fix amount of time, C2.
    The inner for loop runs n - 1, n-2... 3, 2, 1 times.
    This is (n * (n - 1)) / 2, or (n^2 * n) / 2.
    The outer for loop runs n times.

    All of the above put together is C1 + C2 * ((n^2 * n) / 2) * n.
    O(n^2) complexity.
*/
void unique(int* array, int size) {
    int i, j;

    for(i = 0; i < size; i++) {
        //Only check every number pair once.
        for(j = i + 1; j < size; j++) {
            if(array[j] == array[i]) {
                printf("The array doesn't contain unique numbers.\n");
                //The function doesn't need to run anymore at this point.
                return;
            }
        }
    }
    printf("The array contains unique numbers.");
}


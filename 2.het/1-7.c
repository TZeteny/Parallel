#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

int interval();

int main(){
    int range = interval();
    int primes = 0;
    int root;
    int i, j;
    bool prime;
    clock_t t;
    double time_taken;

    t = clock();

    for(i = 2; i < range + 1; i++) {
        root = sqrt(i);
        j = 2;
        prime = true;
        while(j <= root) {
            if(i % j == 0) {
                prime = false;
                break;
            }
            j++;
        }
        if(prime == true) {
            primes += 1;
        }
    }

    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;

    printf("%d\n%lf seconds", primes, time_taken);

    return 0;
}

int interval() {
    int range;
    int ok;
    char ch;

    do {
        ok = 1;
        printf("Interval upper end: ");
        if(scanf("%d", &range) != 1) {
            ok = 0;
            printf("Wrong input!");
            while((ch=getchar()) != '\n');
        }
    }while(!ok);

    return range;
}









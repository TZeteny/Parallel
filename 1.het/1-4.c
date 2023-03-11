#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN 500
#define MAX 1000

int random_int();
float random_float();

int main() {
  int randInt;
  float randFloat;

  printf("random int\n");
  randInt = random_int(MIN, MAX);
  printf("%d\n", randInt);

  printf("\nrandom float\n");
  randFloat = random_float(MIN, MAX);
  printf("%f", randFloat);

  return 0;
}

int random_int(int min, int max) {
    srand(time(NULL));
    int r = (rand() % (max - min + 1)) + min;

    return r;
}

float random_float(int min, int max) {
    srand(time(NULL));
    float r = ((float)rand()/RAND_MAX)*(float)(min) + (500);

    return r;
}

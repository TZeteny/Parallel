#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));
  int randInt;
  float randFloat;

  printf("random int\n");
  randInt = (rand() % (1000 - 500 + 1)) + 500;
  printf("%d\n", randInt);
  
  printf("\nrandom float\n");
  randFloat = ((float)rand()/RAND_MAX)*(float)(500.0) + 500;
  printf("%f", randFloat);

  return 0;
}
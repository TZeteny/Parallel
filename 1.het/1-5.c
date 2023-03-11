#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Needed to return multiple values in read().
struct parameters {
    int number_count, min, max;
};
typedef struct parameters Struct;

Struct read();
void random_number();

int main() {
  Struct s = read();

  random_number(s);

  return 0;
}

Struct read() {
    Struct s;
    int ok;
    char ch;

    do{
      ok = 1;
      printf("How many numbers to generate: ");
      if( scanf("%d", &s.number_count)!=1 ) {
          printf("Wrong input!\n");
          ok = 0;
          while ((ch=getchar())!='\n') ;
      }
      else {
          printf("Minimum, maximum: ");
          if( scanf("%d, %d", &s.min, &s.max)!=2 ) {
          printf("Wrong input!\n");
          ok = 0;
          while ((ch=getchar())!='\n') ;
          }
      }
  }while(!ok);

  return s;
}

void random_number(Struct s) {
    srand(time(NULL));
    int i = 0;

    printf("The random numbers:\n");
    while(i < s.number_count) {
      printf("%d\n", (rand() % (s.max - s.min + 1)) + s.min);
      i++;
    }
}

  return 0;
}

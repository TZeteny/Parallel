#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));
  
  int min, max;
  int howMany;
  
  int ok;
  char ch;
  do{
      ok = 1;
      printf("How many numbers to generate: ");
      if( scanf("%d", &howMany)!=1 ) {
          printf("Wrong input!\n");
          ok = 0;
          while ((ch=getchar())!='\n') ;
      }
      else {
          printf("Minimum, maximum: ");
          if( scanf("%d, %d", &min, &max)!=2 ) {
          printf("Wrong input!\n");
          ok = 0;
          while ((ch=getchar())!='\n') ;
      }
      }
  }while(!ok);
  
  int i;
  while(i < howMany) {
      printf("%d\n", (rand() % (max - min + 1)) + min);
      i++;
  }

  return 0;
}
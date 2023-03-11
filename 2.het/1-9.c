#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct parameters {
    char file_name[50];
    int number_count;
};
typedef struct parameters Struct;

Struct read();

int main() {
    srand(time(0));
    Struct s = read();
    int numbers[s.number_count];
    FILE* fp = fopen(s.file_name, "w");
    int i = 0;
    //For measuring time
    clock_t t;
    double time_taken;

    //Time before execution
    t = clock();
    while(i < s.number_count) {
        numbers[i] = rand();
        i++;
    }
    //Time after execution minus time before exection
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;

    printf("It took %lf seconds to generate the numbers.\n", time_taken);

    //Time before execution
    t = clock();
    i = 0;
    while(i < s.number_count) {
        fprintf(fp, s.file_name, numbers[i]);
        i++;
    }
    //Time after execution minus time before exection
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;

    printf("It took %lf seconds to save the file.\n", time_taken);

    fclose(fp);

    return 0;
}

Struct read() {
    Struct s;
    int ok;
    char ch;

    do{
      ok = 1;
      printf("File name (.txt): ");
      if( scanf("%s", &s.file_name)!=1 ) {
          printf("Wrong input!\n");
          ok = 0;
          while ((ch=getchar())!='\n') ;
      }
      else {
          printf("How many numbers: ");
          if( scanf("%d", &s.number_count)!=1 ) {
          printf("Wrong input!\n");
          ok = 0;
          while ((ch=getchar())!='\n') ;
          }
      }
  }while(!ok);

  return s;
}








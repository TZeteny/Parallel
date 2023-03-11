#include <stdio.h>
#include <stdlib.h>

#define N 5

void writeInt();
void writeLong();
void writeFloat();
void fileSize();
void printFile();

int main() {
  int i[N] = {1, 2, 3, 4, 5};
  long l[N] = {5, 4, 3, 2, 2};
  float f[N] = {1.44, 2.67, 3.564, 4.02, 5.60};

  writeInt(i);
  fileSize("ints.txt");
  printFile("ints.txt");

  writeLong(l);
  fileSize("longs.txt");
  printFile("longs.txt");

  writeFloat(f);
  fileSize("floats.txt");
  printFile("floats.txt");

  return 0;
}

void writeInt(int* array) {
  FILE* fp = fopen("ints.txt", "w");
  if (fp == NULL) {
    printf("Error!\n");
    return;
  }

  for (int i = 0; i < N; i++) {
    fprintf(fp, "%d\n", array[i]);
  }

  fclose(fp);
}

void writeLong(long* array) {
  FILE* fp = fopen("longs.txt", "w");
  if (fp == NULL) {
    printf("Error!");
    return;
  }

  for (int i = 0; i < N; i++) {
    fprintf(fp, "%ld\n", array[i]);
  }

  fclose(fp);
}

void writeFloat(float* array) {
  FILE* fp = fopen("floats.txt", "w");
  if (fp == NULL) {
    printf("Error!");
    return;
  }

  for (int i = 0; i < N; i++) {
    fprintf(fp, "%f\n", array[i]);
  }

  fclose(fp);
}

void fileSize(char name[]) {
  FILE* fp = fopen(name, "r");
  if (fp == NULL) {
    printf("Error!");
    return;
  }

  fseek(fp, 0L, SEEK_END);

  long size = ftell(fp);
  printf("Size of file: %ld\n", size);

  fclose(fp);
}

void printFile(char name[]) {
  FILE* fp = fopen(name, "r");
  if (fp == NULL) {
    printf("Error!");
    return;
  }

  char c = fgetc(fp);
  while (c != EOF) {
    printf("%c", c);
    c = fgetc(fp);
  }

  fclose(fp);
}

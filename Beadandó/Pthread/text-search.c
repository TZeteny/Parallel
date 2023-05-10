/*
Searches for given text in a file.
makefile:
    gcc text-search.c -lpthread -o text-search.exe
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_THREADS 10

typedef struct data {
    int thread_number;
    int split;
    int extra; //extra lines, if number of lines isn't divisble by threads
    char *name;
    char *str;
} Data;

//Search part of the file
void* search_part(void *arg);

int main() {
    char *filename = "text.txt";
    char *search/* = "here"*/; //The searched word
    printf("Searched word: ");
    scanf("%s", search);
    FILE *fp;
    //Checking for error
    if((fp = fopen(filename, "r")) == NULL) {
        perror("Error");
		printf("Error number = %d\n", errno);
        return 1;
	}

	int lines = 0; //The number of lines
	int line_num = 1; //The current line's number
	char ch;

	int threads; //Number of threads
	printf("How many threads: ");
	scanf("%d", &threads);
	if (threads > MAX_THREADS) {
        printf("Exceeded max number of threads.\nNumber is set to maximum of %d.\n", MAX_THREADS);
        threads = 10;
	}
	int split; //Length of split parts
	int extra;
	int thread_no; //thread number
	pthread_t id[threads];

	Data data_arr[threads]; //Data array the size of number of threads
	int i;


	//Count the number of lines
    while(!feof(fp)) {
        ch = fgetc(fp);
        if(ch == '\n') {
            lines++;
        }
    }
    fclose(fp);
    //printf("Number of lines: %d\n", lines);
    split = lines / threads;
    //printf("Split part length: %d\n", split);
    extra = lines % threads;
    //printf("Extra: %d", extra);

    //Create threads
    for (thread_no = 0; thread_no < threads - 1; thread_no++) {
        printf("Creating thread #%d\n", thread_no);
        data_arr[thread_no].thread_number = thread_no;
        data_arr[thread_no].split = split;
        data_arr[thread_no].extra = 0;
        data_arr[thread_no].name = filename;
        data_arr[thread_no].str = search;
        pthread_create(&id[thread_no], NULL, search_part, &data_arr[thread_no]);
    }
    //The last thread, which is given the extra lines
    printf("Creating thread #%d\n", thread_no);
    data_arr[thread_no].thread_number = thread_no;
    data_arr[thread_no].split = split;
    data_arr[thread_no].extra = extra;
    data_arr[thread_no].name = filename;
    data_arr[thread_no].str = search;
    pthread_create(&id[thread_no], NULL, search_part, &data_arr[thread_no]);

    for (i = 0; i < threads; i++) {
        pthread_join(id[i], NULL);
    }

	return 0;
}

void* search_part(void *arg) {
    Data* current_thread_data = (Data*) arg;
    char temp[2048]; //For the currently read line
    char ch;
    FILE *fp = fopen(current_thread_data->name, "r");
    int lines = 0;
    int line_num = 0;

    int start = 0 + current_thread_data->thread_number * current_thread_data->split;
    int end = -1 + (current_thread_data->thread_number + 1) * current_thread_data->split + current_thread_data->extra;
    printf("Thread #%d start: %d , end: %d\n",current_thread_data->thread_number, start + 1, end + 1);
    printf("Searching for: %s\n", current_thread_data->str);

    while(line_num != start && !feof(fp)) {
        ch = fgetc(fp);
        if(ch == '\n') {
            line_num++;
        }
    }
    printf("Thread #%d Line num %d\n", current_thread_data->thread_number, line_num);

    while( (fgets(temp, 2048, fp) != NULL) && line_num <= end)  {
        //Scans the line and finds the first match in it
		if((strstr(temp, current_thread_data->str)) != NULL) {
			printf("Thread %d | Match found on line: %d\n%s\n", current_thread_data->thread_number, line_num + 1, temp);
		}
		line_num++;
    }

    fclose(fp);
    return NULL;
}


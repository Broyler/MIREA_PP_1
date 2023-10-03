/*********************************************

            Практическая работа №7
                  Вариант №3

**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <stdbool.h>

#define TOTAL 10
#define MIN 0
#define MAX 100

void append(int** arr, unsigned long* size, int value) {
    *size = *size + sizeof(int);
    *arr = (int*)realloc(*arr, *size);
    (*arr)[(*size / sizeof(int)) - 1] = value;  
}

bool checkSeq(int* arr, unsigned long size) {
    if (size / sizeof(int) < 2) return false;
    for (int i = 1; i < size / sizeof(int); ++i) {
        if (arr[i] < arr[i - 1]) return false;
    }
    return true;
}

int main(void) {
    srand(time(NULL));
    int nums[TOTAL];
    int c = 0;

    for (int i = 0; i < TOTAL; ++i) {
        nums[i] = rand() % (MAX - MIN + 1) + MIN;
        printf("%4d ", nums[i]);
    }

    int* arr = NULL;
    unsigned long size = 0;

    for (int i = 0; i < TOTAL - 1; ++i) {
        for (int j = i + 1; j < TOTAL; ++j) {
            arr = NULL;
            size = 0;

            for (int k = i; k <= j; ++k) {
                append(&arr, &size, nums[k]);
            }

            if (checkSeq(arr, size)) c++;
            free(arr);
        }
    }

    printf("\nSequences: %d", c);
    return 0;
}
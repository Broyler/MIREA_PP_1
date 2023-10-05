/*********************************************

            Практическая работа №9
                  Вариант №3

**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <stdbool.h>

#define TOTAL 10
#define MIN 0
#define MAX 10

void append(int** arr, unsigned long* size, int value) {
    *size = *size + sizeof(int);
    *arr = (int*)realloc(*arr, *size);
    (*arr)[(*size / sizeof(int)) - 1] = value;
}

void findAll(int** arr, unsigned long* size, int element) {
    for (int i = 0; i < *size / sizeof(int); ++i) {
        if (*arr[i] == element) append(arr, size, i);
    }
}

int main(void) {
    srand(time(NULL));
    int *nums;
    unsigned long c = 0;
    int element = 5;

    for (int i = 0; i < TOTAL; ++i) {
        append(&nums, &c, rand() % (MAX - MIN + 1) + MIN);
    }

    int *occ;
    unsigned long occSize = 0;
    findAll(&occ, &occSize, element);

    for (int i = 0; i < occSize / sizeof(int); ++i) {
        printf("%4d ", occ[i]);
    }
}
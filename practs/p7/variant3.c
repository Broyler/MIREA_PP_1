/*********************************************

            Практическая работа №9
                  Вариант №3

**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <stdbool.h>

#define TOTAL 100
#define MIN -100
#define MAX 100

void append(int** arr, unsigned long* size, int value) {
    *size = *size + sizeof(int);
    *arr = (int*)realloc(*arr, *size);
    (*arr)[(*size / sizeof(int)) - 1] = value;  
}

int* findAll(int* arr, unsigned long size, int element) {
    int *result;
    unsigned long resSize = 0;
    for (int i = 0; i < size / sizeof(int); ++i) {
        if (arr[i] == element) append(&result, &resSize, i);
    }
    return result;
}

int main(void) {
    srand(time(NULL));
    int *nums;
    unsigned long c = 0;
    int element = 5;

    for (int i = 0; i < TOTAL; ++i) {
        append(&nums, &c, rand() % (MAX - MIN + 1) + MIN);
        printf("%4d ", nums[i]);
    }

    int *occ, uns = findAll(nums, c, element);
    for

}
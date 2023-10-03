/*********************************************

            Практическая работа №7
                  Вариант №6

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

bool checkSeq(int* arr, unsigned long size) {
    for (int i = 0; i < size / sizeof(int); ++i) {
        if (arr[i] <= 0) return false;
    }
    return true;
}

int findSum(int* arr, unsigned long size) {
    int result = 0;
    for (int i = 0; i < size / sizeof(int); ++i) {
        result = result + arr[i];
    }
    return result;
}

int main(void) {
    srand(time(NULL));
    int nums[TOTAL];
    int maxSum = -1;

    for (int i = 0; i < TOTAL; ++i) {
        nums[i] = rand() % (MAX - MIN + 1) + MIN;
        printf("%4d ", nums[i]);
    }

    int* arr = NULL;
    unsigned long size = 0;

    for (int i = 0; i < TOTAL - 1; ++i) {
        for (int j = i; j < TOTAL; ++j) {
            arr = NULL;
            size = 0;

            for (int k = i; k <= j; ++k) {
                append(&arr, &size, nums[k]);
            }

            if (checkSeq(arr, size)) {
                int res = findSum(arr, size);
                if (res > maxSum) maxSum = res;
            }
            free(arr);
        }
    }

    printf("\nMax sum: %d", maxSum);
    return 0;
}
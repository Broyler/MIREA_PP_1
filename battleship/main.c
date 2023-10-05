#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {EMPTY, ALIVE, HIT, DEAD} state;

#define SIDE 10

void fillArray(int (*arr)[SIDE][SIDE]) {
    FILE* ptr;
    char ch;
    int row = 0;
    int col = 0;
    ptr = fopen("ships.txt", "r");
    if (ptr == NULL) {
        printf("No ships.txt file found\n");
        return;
    }
    do {
        ch = (char)fgetc(ptr);
        if (ch == '\n') {
            row++;
            col = 0;
        }
        if (ch == ' ') col++;
        if (ch == '.') (*arr)[row][col] = 0;
        if (ch == 'x') (*arr)[row][col] = 1;
    } while (ch != EOF);
    fclose(ptr);
}

void display(int arr[SIDE][SIDE]) {
    for (int i = 0; i < SIDE; ++i) {
        for (int j = 0; j < SIDE; ++j) {
            switch (arr[i][j]) {
                case EMPTY:
                    printf(". ");
                    break;

                case ALIVE:
                    printf("o ");
                    break;

                case HIT:
                    printf("x ");
                    break;

                case DEAD:
                    printf("X ");
                    break;
            }
        }
        if (i == SIDE - 1) return;
        printf("\n");
    }
}

int main()
{
    int ships[SIDE][SIDE];
    fillArray(&ships);
    display(ships);

    return 0;
}
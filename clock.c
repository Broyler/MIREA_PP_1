#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define W 60
#define H 30
#define PADDING_LEFT 10
#define PADDING_TOP 5
#define SECONDS_LEN 20
#define PI 3.14159265359
#define STEPS 20

void clr() {
    printf("\e[1;1H\e[2J");
}

void test_fill() {
    for (int i = 0; i < PADDING_TOP; ++i) printf("\n");
    for (int i = 0; i < H; ++i) {
        for (int pl = 0; pl < PADDING_LEFT; ++pl) printf(" ");
        for (int j = 0; j < W; ++j) {
            printf(".");
        }
        printf("\n");
    }
}

void draw_seconds(int second) {
    char pad[H][W];
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            pad[i][j] = '.';
        }
    }

    const double point = PI / 2.0f - ((double)second / 60.0f) * 2.0f * PI;
    const int endX = (W / 2) + round(SECONDS_LEN * cos(point));
    const int endY = (H / 2) - round(SECONDS_LEN / (W / H) * sin(point));
    const int startX = W / 2;
    const int startY = H / 2;
    int col;
    int row;

    for (int i = 0; i <= STEPS; ++i) {
        col = round(startY + ((double)i / STEPS) * (endY - startY));
        row = round(startX + ((double)i / STEPS) * (endX - startX));
        printf("%d\n", col);
        pad[col][row] = 'X';
    }

    clr();
    for (int i = 0; i < PADDING_TOP; ++i) printf("\n");
    for (int i = 0; i < H; ++i) {
        for (int pl = 0; pl < PADDING_LEFT; ++pl) printf(" ");
        for (int j = 0; j < W; ++j) {
            printf("%c", pad[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        if (
            strcmp(argv[1], "-f") == 0 || 
            strcmp(argv[1], "-fill") == 0
        ) test_fill();
    }
    
    for (int sec = 0; sec < 60; ++sec) {
        draw_seconds(sec);
        sleep(1);
    }
} 
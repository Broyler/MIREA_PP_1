#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#ifdef WIN32
#include <windows.h>
#endif

#define W 60
#define H 30
#define PADDING_LEFT 10
#define PADDING_TOP 5
#define SECONDS_LEN 26
#define MINUTE_LEN 18
#define HOUR_LEN 10
#define PI 3.14159265359
#define STEPS 30
#define CLOCKROUND_RAD 29

void sleep_ms(int milliseconds) {
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    if (milliseconds >= 1000)
      sleep(milliseconds / 1000);
    usleep((milliseconds % 1000) * 1000);
#endif
}


long long time_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}


void clr() {
    //printf("\e[1;1H\e[2J");
    system("cls");
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

void draw_seconds(char (*pad)[H][W], int second, int arrowLen, char symbol) {
    const double point = PI / 2.0f - ((double)second / 60.0f) * 2.0f * PI;
    const int endX = (W / 2) + round(arrowLen * cos(point));
    const int endY = (H / 2) - round(arrowLen / (W / H) * sin(point));
    const int startX = W / 2;
    const int startY = H / 2;
    int col;
    int row;

    for (int i = 0; i <= STEPS; ++i) {
        col = round(startY + ((double)i / STEPS) * (endY - startY));
        row = round(startX + ((double)i / STEPS) * (endX - startX));
        (*pad)[col][row] = symbol;
    }
}

void render(char pad[H][W]) {
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

    long long ltime;
    long long ftime;
    long long ttime;
    int wait_for;
    time_t now;
    struct tm *tm;
    int sec, minute, hour;
    double angle;
    int xcol, xrow;

    for (;;) {
        ltime = time_ms();
        now = time(0);
        tm = localtime(&now);
        sec = tm->tm_sec;
        minute = tm->tm_min;
        hour = tm->tm_hour;
        char pad[H][W];
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                pad[i][j] = ' ';
            }
        }

        for (int i = 0; i < 360; ++i) {
            angle = i * (PI / 180);
            xcol = round((H / 2) - round(CLOCKROUND_RAD / (W / H) * sin(angle)));
            xrow = round((W / 2) + round(CLOCKROUND_RAD * cos(angle)));
            pad[xcol][xrow] = 'o';
        }
        draw_seconds(&pad, sec, SECONDS_LEN, 'X');
        draw_seconds(&pad, minute, MINUTE_LEN, 'O');
        draw_seconds(&pad, (hour % 12) * 5, HOUR_LEN, '+');
        render(pad);
        ftime = time_ms();
        ttime = ftime - ltime;
        wait_for = 1000 - ttime;
        sleep_ms(wait_for);
    }
} 
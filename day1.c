#include <stdio.h>
#include <string.h>

int mod(int a, int b) {
    int r = a % b;
    return r < 0 ? r + b : r;
}

int problem_1(int cursor, int dir, int clicks, int *result) {
    cursor = mod(cursor + dir * clicks, 100);
    if (cursor == 0) *result = *result + 1;
    return cursor;
}

int problem_2(int cursor, int dir, int clicks, int *result) {
    for (int i = 1; i <= clicks; i++) {
        cursor = mod(cursor + dir, 100);
        if (cursor == 0) *result = *result + 1;
    }
    return cursor;
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        int result = 0;
        int c;
        int dir;
        int clicks = 0;
        int cursor = 50;
        FILE *fp;
        fp = fopen(argv[2], "r");

        while ((c = fgetc(fp)) != EOF) {
            if (c == 'L') {
                dir = -1;
            } else if (c == 'R') {
                dir = 1;
            } else if (c == '\n') {
                if (strcmp(argv[1], "part1") == 0) {
                    cursor = problem_1(cursor, dir, clicks, &result);
                    clicks = 0;
                } else if (strcmp(argv[1], "part2") == 0) {
                    cursor = problem_2(cursor, dir, clicks, &result);
                    clicks = 0;
                } else {
                    return -1;
                }
            } else {
                clicks = clicks * 10 + c - '0';
            }
        }

        fclose(fp);
        printf("Result for %s: %d\n", argv[1], result);
        return 0;
    } else {
        return -1;
    }
}

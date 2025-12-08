#include <stdio.h>
#include <stdlib.h>

unsigned int check_neighbours(int idx, int *arr, unsigned int cols, unsigned int len) {
    int neighbours = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int neighbour_idx = idx + i * (cols + 1) + j;
            if (neighbour_idx == idx) continue;
            if (neighbour_idx < 0 || neighbour_idx > len) continue;
            if (arr[neighbour_idx] == 1) neighbours++;
        }
    }

    if (neighbours < 4) {
        return 1;
    } else {
        return 0;
    }
}

void problem1(int *arr, unsigned int cols, unsigned int len, unsigned int *sum) {
    for (int i = 0; i < len; i++) {
        if (arr[i] == 1) {
            *sum = *sum + check_neighbours(i, arr, cols, len);
        }
    }
}

void problem2(int *arr, unsigned int cols, unsigned int len, unsigned int *sum) {
    int removed = 0;

    do {
        removed = 0;

        for (int i = 0; i < len; i++) {
            if (arr[i] == 1 && check_neighbours(i, arr, cols, len) == 1) {
                arr[i] = 2;
                removed++;
            }
        }

        *sum = *sum + removed;

        for (int i = 0; i < len; i++) {
            if (arr[i] == 2) {
                arr[i] = 0;
            }
        }
    } while (removed > 0);
}

int main(int argc, char *argv[]) {
    FILE *fp;
    int c;
    fp = fopen(argv[1], "r");
    int *arr = (int *)malloc(1 * sizeof(int));
    unsigned int sum1 = 0;
    unsigned int sum2 = 0;
    unsigned int len = 0;
    unsigned int cols = 0;
    unsigned int rows = 0;

    while ((c = fgetc(fp)) != EOF) {
        len++;
        int *tarr = (int *)realloc(arr, len * sizeof(int));
        arr = tarr;
        if (c == '\n') {
            rows++;
            arr[len - 1] = -1;
        } else if (c == '.') {
            cols++;
            arr[len - 1] = 0;
        } else {
            cols++;
            arr[len - 1] = 1;
        }
    }

    problem1(arr, cols / rows, len, &sum1);
    problem2(arr, cols / rows, len, &sum2);

    printf("Solution to part 1: %d\n", sum1);
    printf("Solution to part 2: %d\n", sum2);

    free(arr);
    fclose(fp);
    return 0;
}

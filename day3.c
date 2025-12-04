#include <stdio.h>
#include <stdlib.h>

void solve(unsigned long *voltage, int *arr, int len, int max) {
    int idx = -1;
    for (int c = max - 1; c >= 0; c--) {
        int max = 0;

        for (int i = idx + 1; i < len - c; i++) {
            if (arr[i] > max) {
                max = arr[i];
                idx = i;
            }
        } 

        *voltage = *voltage * 10 + max;
    }
}

void problem1(int *arr, int len, unsigned long *sum) {
    unsigned long voltage = 0;
    solve(&voltage, arr, len, 2);
    *sum = *sum + voltage;
}

void problem2(int *arr, int len, unsigned long *sum) {
    unsigned long voltage = 0;
    solve(&voltage, arr, len, 12);
    *sum = *sum + voltage;
}

int main(int argc, char *argv[]) {
    FILE *fp;
    int c;
    fp = fopen(argv[1], "r");
    int len = 0;
    int *arr = (int *)malloc(1 * sizeof(int));
    unsigned long sum1 = 0;
    unsigned long sum2 = 0;
    
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            problem1(arr, len, &sum1);
            problem2(arr, len, &sum2);

            for (int i = 0; i < len; i++) {
                arr[i] = 0;
            }

            len = 0;
        } else {
            len++;
            int *tarr = (int *)realloc(arr, len * sizeof(int));
            arr = tarr;
            int digit = c - '0';
            arr[len - 1] = digit;
        }
    }

    printf("Solution to part 1: %ld\n", sum1);
    printf("Solution to part 2: %ld\n", sum2);

    free(arr);
    fclose(fp);
    return 0;
}

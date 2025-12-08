#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void problem1(unsigned long long (*intervals)[2], int len, unsigned long long id, int *sum) {
    for (int i = 0; i < len; i++) {
        if (intervals[i][0] <= id && id <= intervals[i][1]) {
            *sum = *sum + 1;
            break;
        }
    }
}

void problem2(unsigned long long (*ints)[2], int len, unsigned long long *sum) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (ints[j][0] > ints[j + 1][0]) {
                unsigned long long tmp0 = ints[j][0];
                unsigned long long tmp1 = ints[j][1];
                ints[j][0] = ints[j + 1][0];
                ints[j][1] = ints[j + 1][1];
                ints[j + 1][0] = tmp0;
                ints[j + 1][1] = tmp1;
            }
        }
    }

    unsigned long long min = ints[0][0];
    unsigned long long max = ints[0][1];

    for (int i = 1; i < len; i++) {
        if (max + 1 >= ints[i][0]) {
            if (ints[i][1] > max) {
                max = ints[i][1];
            }
        } else {
            *sum = *sum + max - min + 1;
            min = ints[i][0];
            max = ints[i][1];
        }
    }

    *sum = *sum + max - min + 1;
}

int main(int argc, char *argv[]) {
    FILE *fp;
    fp = fopen(argv[1], "r");
    char line[256];
    int len = 0;
    int sum1 = 0;
    unsigned long long sum2 = 0;
    unsigned long long (*intervals)[2] = malloc(1 * sizeof(unsigned long long[2]));

    while (fgets(line, sizeof(line), fp)) {
        if (strcmp(line, "\n") == 0) break;

        len++;
        unsigned long long (*intervals_tmp)[2] = realloc(intervals, len * sizeof(unsigned long long[2]));
        intervals = intervals_tmp;

        char *line_copy = strdup(line);
        line_copy[strcspn(line, "\n")] = '\0';

        char *min = strtok(line_copy, "-");
        char *max = strtok(NULL, "-");

        intervals[len - 1][0] = atoll(min);
        intervals[len - 1][1] = atoll(max);

        free(line_copy);
    }

    while (fgets(line, sizeof(line), fp)) {
        char *line_copy = strdup(line);
        line_copy[strcspn(line, "\n")] = '\0';

        unsigned long long id = atoll(line_copy);
        problem1(intervals, len, id, &sum1);

        free(line_copy);
    }

    problem2(intervals, len, &sum2);

    printf("Solution to part 1: %d\n", sum1);
    printf("Solution to part 2: %lld\n", sum2);

    free(intervals);
    fclose(fp);
    return 0;
}

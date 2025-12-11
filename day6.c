#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void problem1(char *file, unsigned long long *sum) {
    FILE *fp;
    fp = fopen(file, "r");
    char line[4096];
    int **matrix = (int **)malloc(1 * sizeof(int *));
    int rows = 0;
    int cols = 0;

    // parse
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';

        matrix = (int **)realloc(matrix, (rows + 1) * sizeof(int *));

        // get number of columns
        if (rows == 0) {
            char *tmp = strdup(line);
            char *token = strtok(tmp, " ");
            while (token) {
                cols++;
                token = strtok(NULL, " ");
            }
            free(tmp);
        }

        // allocate number of columns
        matrix[rows] = (int *)malloc(cols * sizeof(int));

        // parse and insert into matrix
        char *token = strtok(line, " ");
        int col = 0;
        while (token) {
            if (strcmp(token, "*") == 0) {
                matrix[rows][col] = 0;
            } else if (strcmp(token, "+") == 0) {
                matrix[rows][col] = 1;
            } else {
                matrix[rows][col] = atoi(token);
            }
            token = strtok(NULL, " ");
            col++;
        }
        rows++;
    }

    for (int c = 0; c < cols; c++) {
        int op = matrix[rows - 1][c];

        if (op == 0) {
            unsigned long long addend = 1;
            for (int r = 0; r < rows - 1; r++) {
                addend = addend * matrix[r][c];
            }
            *sum = *sum + addend;
        } else {
            unsigned long long addend = 0;
            for (int r = 0; r < rows - 1; r++) {
                addend = addend + matrix[r][c];
            }
            *sum = *sum + addend;
        }
    }

    free(matrix);
    fclose(fp);
}

void problem2(char *file, unsigned long long *sum) {
    FILE *fp;
    int c;
    fp = fopen(file, "r");
    int **matrix = (int **)malloc(1 * sizeof(int *));
    int *row = (int *)malloc(1 * sizeof(int));
    int rows = 0;
    int cols = 0;
    int col = 0;

    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            matrix = (int **)realloc(matrix, (rows + 1) * sizeof(int *));
            matrix[rows] = row;
            row = NULL;
            col = 0;
            rows++;
        } else {
            row = (int *)realloc(row, (col + 1) * sizeof(int));

            if (c == '*') {
                row[col] = -1;
            } else if (c == '+') {
                row[col] = -2;
            } else if (c == ' ') {
                row[col] = 0;
            } else {
                row[col] = c - '0';
            }

            col++;
            cols++;
        }
    }

    unsigned long long addend1 = 0;
    unsigned long long addend2 = 1;
    for (int i = cols / rows - 1; i >= 0; i--) {
        int all_zero = 0;
        int factor = 0;
        for (int j = 0; j < rows - 1; j++) {
            if (matrix[j][i] != 0) {
                all_zero = 1;
                factor = factor * 10 + matrix[j][i];
            }
        }

        if (all_zero == 0) continue;

        addend1 += factor;
        addend2 *= factor;

        if (matrix[rows - 1][i] == -1) {
            *sum = *sum + addend2; 
            addend1 = 0;
            addend2 = 1;
        } else if (matrix[rows - 1][i] == -2) {
            *sum = *sum + addend1;
            addend1 = 0;
            addend2 = 1;
        }
    }

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }

    free(matrix);
    fclose(fp);
}

int main(int argc, char *argv[]) {
    unsigned long long sum1 = 0;
    unsigned long long sum2 = 0;

    problem1(argv[1], &sum1);
    problem2(argv[1], &sum2);

    printf("Solution to part 1: %llu\n", sum1);
    printf("Solution to part 2: %llu\n", sum2);

    return 0;
}

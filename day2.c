#include <stdio.h>
#include <string.h>

long unsigned pow_ten(int d) {
    long unsigned pow = 1;
    for (int i = 0; i < d; i++) {
        pow = pow * 10;
    }
    return pow;
}

int get_no_digits(unsigned long id) {
    int no_digits = 0;

    while (id != 0) {
        id = id / 10;
        no_digits++;
    }

    return no_digits;
}

void problem1(unsigned long min, unsigned long max, unsigned long *sum) {
    for (unsigned long id = min; id <= max; id++) {
        int no_digits = get_no_digits(id);
        long unsigned split = pow_ten(no_digits / 2);
        unsigned long left = id / split;
        unsigned long right = id % split;
        if (no_digits % 2 == 0 && left == right) *sum = *sum + id;
    }
}

void problem2(unsigned long min, unsigned long max, unsigned long *sum) {
    for (unsigned long id = min; id <= max; id++) {
        int no_digits = get_no_digits(id);

        if (no_digits == 1) continue;

        for (int i = 1; i <= no_digits / 2; i++) {
            unsigned long partitions[no_digits / i];

            if (no_digits % i != 0) continue;
            
            for (int j = 0; j < no_digits / i; j++) {
                partitions[j] = 0;
            }

            unsigned long tmp = id;
            for (int j = 0; j < no_digits; j++) {
                long unsigned digit = tmp % 10;
                int bucket = j / i;
                tmp = tmp / 10;
                partitions[bucket] = partitions[bucket] * 10 + digit;
            }


            int all_same = 0;
            for (int j = 0; j < no_digits/ i; j++) {
                if (partitions[j] != partitions[0]) {
                    all_same = -1;
                    break;
                }
            }

            if (all_same == 0) {
                *sum = *sum + id;
                break;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *fp;
    fp = fopen(argv[1], "r");

    int c;
    int track = 0;
    unsigned long min = 0;
    unsigned long max = 0;
    unsigned long sum1 = 0;
    unsigned long sum2 = 0;

    while (1) {
        c = fgetc(fp);

        if (c == '-') {
            track = 1;
        } else if (c == ',' || c == EOF) {
            problem1(min, max, &sum1);
            problem2(min, max, &sum2);
            min = 0;
            max = 0;
            track = 0;

            if (c == EOF) break;
        } else if (c == '\n') {
            continue;
        } else {
            if (track == 0) {
                min = min * 10 + c - '0';
            } else {
                max = max * 10 + c - '0';
            }
        }
    }

    printf("Solution to part 1: %ld\n", sum1);
    printf("Solution to part 2: %ld\n", sum2);

    fclose(fp);
    return 0;
}

//
// Created by cthulhu on 14/10/2021.
//

#include <stdio.h>
#include <math.h>
#include "lib/binomial_table.c"
#include "lib/multi_table.c"

int read_iteration(const char*, struct MultiTable*);
void read_input(const char*, struct Table*, int, int*, double*);

int main(int argc, char** argv) {
    struct MultiTable binomial_table = create_binomial_table("data/binomial.csv");

    if (argc > 1 && strcmp(argv[1], "-p") == 0) {
        print_multi_table(&binomial_table);

        return 0;
    }

    int iteration = read_iteration("Input iteration number: ", &binomial_table);

    struct Table* table = find_table(binomial_table, iteration);

    if (table == NULL) {
        printf("Unexpected behaviour!\n");
        exit(1);
    }

    int index;
    double precision;
    read_input("Input searching number: ", table, iteration, &index, &precision);

    char* error = (char*)malloc(sizeof(char) * 256);
    error[0] = '\0';

    double value = get_value(*table, index, precision, &error);

    if (error[0]) {
        printf("[Error]: %s\n", error);
        exit(1);
    } else {
        printf("Value is %lf\n", value);
    }

    return 0;
}

int read_iteration(const char* msg, struct MultiTable* data) {
    if (data == NULL)
        return 0;

    int index;
    char* input = (char*)malloc(sizeof(char) * 256);

    do {
        printf("%s", msg);
        scanf("%s", input);
        index = atoi(input);
    } while(index > 0 && find_table(*data, index) == NULL);

    return index;
}

void read_input(const char* msg, struct Table* content, int iteration, int* index_ptr, double* precision_ptr) {
    if (content == NULL)
        return;

    double n, precision;
    int index;
    do {
        printf("%s", msg);
        scanf("%lf", &n);

        index = floor(n);
        precision = n - index;
    } while(index > iteration || get_value(*content, index, precision, NULL) == -1);

    *index_ptr = index;
    *precision_ptr = precision;
}

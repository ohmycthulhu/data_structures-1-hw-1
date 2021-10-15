//
// Created by cthulhu on 11/10/2021.
//
#ifndef ARRAY_C
#define ARRAY_C

//
// Created by cthulhu on 11/10/2021.
//
#include <stdlib.h>
#include <string.h>
#include "file.c"
#include "math.c"

#define NEG_VALUE 1.0e-4

/**
 * Declarations
 * */

struct Array {
    double* values;
    size_t size;
};

int find_index(struct Array, double);
void add_to_array(struct Array * array, double element);
void print_array(struct Array* array);
int approximately_equal(double x1, double x2);

/**
 * Implementation
 * */

int find_index(const struct Array array, double num) {
    for (int i = 0; i < array.size; i++) {
        if (approximately_equal(array.values[i], num)) {
            return i;
        }
    }

    return -1;
}

void add_to_array(struct Array * array, double element) {
    if (array->values) {
        array->values = (double *) realloc(array->values, sizeof(double) * (array->size + 1));
    } else {
        array->values = (double*) malloc(sizeof(double));
    }
    array->values[array->size] = element;
    array->size++;
}

void print_array(struct Array* array) {
    if (array == NULL)
        return;

    for(int i = 0; i < array->size; i++) {
        if (i != 0)
            printf(", ");

        printf("%lf", array->values[i]);
    }
    printf("\n");
}

int approximately_equal(double x1, double x2) {
  return (fabs(x1 - x2)) < NEG_VALUE;
}

#endif

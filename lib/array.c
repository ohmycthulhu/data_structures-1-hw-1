//
// Created by cthulhu on 11/10/2021.
//
#ifndef ARRAY_C
#define ARRAY_C

#include <stdlib.h>
#include <string.h>
#include "file.c"
#include "math.c"

/**
 * Declarations
 * */

/**
 * Structure for containing the information about simple array
 * */
struct Array {
    double *values;
    size_t size;
};

/**
 * Function for finding index of value
 * Returns -1 if fails
 * */
int find_index(struct Array, double);

/**
 * Function for adding an element into the array
 * */
void add_to_array(struct Array *array, double element);

/**
 * Function for printing the content of array
 * */
void print_array(struct Array *array);

/**
 * Function for generating array with n elements from a range
 * */
struct Array generate_array(double start, double end, int n);

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

void add_to_array(struct Array *array, double element) {
  /*
   * If values exists, then reallocate it to new size
   * Else allocate memory for 1 element
   * */
  if (array->values) {
    array->values = (double *) realloc(array->values, sizeof(double) * (array->size + 1));
  } else {
    array->values = (double *) malloc(sizeof(double));
  }

  // Actually add the element to the array and increase the size information
  array->values[array->size++] = element;
}

void print_array(struct Array *array) {
  if (array == NULL)
    return;

  // Print array in form of\
  // el1, el2, el3\n
  for (int i = 0; i < array->size; i++) {
    if (i != 0)
      printf(", ");

    printf("%lf", array->values[i]);
  }
  printf("\n");
}

struct Array generate_array(double start, double end, int n) {
  /*
   * Define the step as (end - start) / n
   * Allocate all items inside the array
   * */
  double *content = (double *) malloc(sizeof(double) * n);
  double step = (end - start) / n;
  int i = 0;
  for (double s = start; s <= end; s += step, ++i) {
    content[i] = s;
  }

  struct Array result = {content, n};
  return result;
}

#endif

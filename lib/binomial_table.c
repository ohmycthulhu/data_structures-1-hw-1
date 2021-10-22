//
// Created by cthulhu on 13/10/2021.
//
#ifndef BINOMIAL_TABLE_C
#define BINOMIAL_TABLE_C

#include "file.c"
#include "multi_table.c"
#include "table.c"
#include "array.c"

/**
 * This file contains specific functions for working with binomial.csv
 * It has the interface close to the usual_table.c
 * */

/**
 * Declarations
 * */

/**
 * Function for reading content of binomial.csv in multi-table data structure
 * This function works with the open file
 * */
struct MultiTable read_binomial_table(FILE *file, int evenly_spaced);

/**
 * Function for reading content of binomial.csv in multi-table data structure
 * It creates temporary file for working
 * */
struct MultiTable create_binomial_table(const char *src, int evenly_spaced);

/**
 * Function for reading the first row in Array structure
 * */
struct Array read_binomial_headers(FILE *file);

/**
 * Function for getting the index of subtable (index of "5;0;0.3;..." is 5)
 * */
int get_iteration_size(FILE *file);

/**
 * Function for reading the content of subtable
 * It also moves the pointer to the start of next subtable
 * */
struct Table get_iteration_content(FILE *file, struct Array headers, int iteration_size);

/**
 * Implementations
 * */
struct MultiTable read_binomial_table(FILE *file, int evenly_spaced) {
  // Get headers
  struct Array headers = read_binomial_headers(file);

  // Skip 2 lines
  skip_line(file);
  skip_line(file);

  // Count the iterations count
  // And collect indices array
  int iteration_size;
  struct Array indices = {NULL, 0};

  while ((iteration_size = get_iteration_size(file)) > 0) {
    add_to_array(&indices, iteration_size);
  }

  // Reset to the start and skip header lines
  reset_pointer(file);
  skip_line(file);
  skip_line(file);

  // Get the iteration size
  int constant_size = evenly_spaced ? (count_lines(file) - 2) / indices.size : -1;
  struct Table *contents = (struct Table *) malloc(sizeof(struct Table) * indices.size);

  for (int i = 0; i < indices.size; i++) {
    iteration_size = constant_size > 0 ? constant_size : (indices.values[i] + 1);
    contents[i] = get_iteration_content(file, headers, iteration_size);
  }

  return generate_multi_table(contents, indices);
}

struct MultiTable create_binomial_table(const char *src, int evenly_spaced) {
  char *tmp_file = (char *) malloc(sizeof(char) * 256);
  sprintf(tmp_file, "temp/table-%li.csv", random());
  // Create intermediate file
  replace_character(src, tmp_file, ',', '.');

  // Open file
  FILE *file = fopen(tmp_file, "r");

  // Get the result
  struct MultiTable result = read_binomial_table(file, evenly_spaced);

  // Close file
  fclose(file);

  return result;
}

struct Array read_binomial_headers(FILE *file) {
  reset_pointer(file);

  int size = count_numbers(file) - 2;
  double *numbers = (double *) malloc(sizeof(double) * size);

  reset_pointer(file);

  // Skip the p;; in beginning
  fscanf(file, "p;");

  // Read every number ;{number}
  for (int i = 0; i < size; i++) {
    fscanf(file, ";%lf", numbers + i);
  }

  reset_pointer(file);

  struct Array result = {
      numbers,
      size
  };

  return result;
}

int get_iteration_size(FILE *file) {
  while(1) {
    int c, result;
    c = getc(file);
    if (c == EOF)
      return -1;
    if (c > 48 && c < 58) {
      fseek(file, -1, SEEK_CUR);
      fscanf(file, "%i", &result);
      return result;
    }
    skip_line(file);
  }
}

struct Table get_iteration_content(FILE *file, struct Array headers, int iteration_size) {
  double *columns_data = (double *) malloc(sizeof(double) * iteration_size);

  double **content_values = (double **) malloc(sizeof(double *) * iteration_size);

  int t;
  for (int i = 0; i < iteration_size; i++) {
    if (i == 0) {
      fscanf(file, "%i;", &t);
    } else {
      fscanf(file, ";");
    }
    fscanf(file, "%lf", columns_data + i);

    content_values[i] = (double *) malloc(sizeof(double) * headers.size);
    for (int j = 0; j < headers.size; j++) {
      fscanf(file, ";%lf", content_values[i] + j);
    }

    skip_line(file);
  }

  struct Matrix content = {.matrix=content_values, .n=iteration_size, .m=headers.size};
  struct Array columns = {.values=columns_data, .size=iteration_size};

  struct Table result = {headers, columns, content};

  return result;
}

#endif

//
// Created by cthulhu on 11/10/2021.
//
#ifndef TABLE_C
#define TABLE_C
#include <string.h>
#include "file.c"
#include "matrix.c"
#include "array.c"

/**
 * Declarations
 * */

/**
 * Structure for working with table
 * */
struct Table {
    struct Array headers;
    struct Array columns;
    struct Matrix content;
};

/**
 * Tries to get value from cell, defined by row and column value
 * If there is no value, sets *error to error message
 * */
double get_value(struct Table table, double n, double m, char** error);

/**
 * Prints the content of the table
 * */
void print_table(struct Table *table);

/**
 * Writes the table into the file in csv format
 * */
void write_table_to_csv_file(const char* path, struct Table);

/**
 * Implementation
 * */

double get_value(struct Table table, double n, double m, char** error) {
    int i = find_index(table.columns, n);
    int j = find_index(table.headers, m);

    if (i < 0 || j < 0) {
        if (error != NULL) {
            *error = "Some of value doesn't exist";
        }
        return -1;
    }

    return table.content.matrix[i][j];
}

void print_table(struct Table *table) {
    if (table == NULL)
        return;

    int i, j;

    // Print the header
    for (i = 0; i < table->headers.size; i++) {
        printf("\t");
        printf("%lf", table->headers.values[i]);
    }
    printf("\n");

    // Print the rows
    for (i = 0; i < table->columns.size; i++) {
        // Print the first column
        printf("%lf", table->columns.values[i]);

        // Print the rest
        for (j = 0; j < table->headers.size; j++) {
            printf("\t%lf", table->content.matrix[i][j]);
        }
        printf("\n");
    }
}

void write_table_to_csv_file(const char* path, struct Table table) {
  const char* file_name = "temp/write_table.csv";
  // Open file
  FILE* file = fopen(file_name, "w");

  if (!file) {
    return;
  }
  int i, j;

  // Write header
  for(i = 0; i < table.headers.size; i++) {
    fprintf(file, ";%lf", table.headers.values[i]);
  }
  fprintf(file, "\n");

  // Write content
  for (i = 0; i < table.columns.size; i++) {
    // Write the column
    fprintf(file, "%lf", table.columns.values[j]);

    // Write the rest of content
    for (j = 0; j < table.headers.size; j++) {
      fprintf(file, ";%lf", table.content.matrix[i][j]);
    }

    fprintf(file, "\n");
  }

  // Close the file
  fclose(file);

  // Copy file with replacing
  replace_character(file_name, path, '.', ',');
}

#endif

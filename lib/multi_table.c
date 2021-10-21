//
// Created by cthulhu on 13/10/2021.
//
#ifndef MULTI_TABLE_C
#define MULTI_TABLE_C

#include "table.c"

/**
 * Declarations
 * */

/**
 * A pointer to the table inside multi-table
 * */
struct TableDescriptor {
    int index;
    struct Table *table;
};

/**
 * Data structure for containing several matrices with keys as indices
 * */
struct MultiTable {
    struct TableDescriptor *tables;
    size_t size;
};

/**
 * Function for finding a table by index. Returns NULL if table doesn't exists
 * */
struct Table *find_table(struct MultiTable multiTable, int index);

/**
 * Function for generating a multi-table for generating multi-table
 * It's crucial that indices and tables have equal length
 * */
struct MultiTable generate_multi_table(struct Table *tables, struct Array indices);

/**
 * Function for printing the content of multi-table
 * */
void print_multi_table(struct MultiTable *multi_table);

/**
 * Function for writing multi-table to .csv file
 * */
void save_multi_table_in_file(const char *path, struct MultiTable *multi_table);

/**
 * Implementations
 * */
struct Table *find_table(struct MultiTable multiTable, int index) {
  for (int i = 0; i < multiTable.size; i++) {
    if (multiTable.tables[i].index == index) {
      return multiTable.tables[i].table;
    }
  }

  return NULL;
}

struct MultiTable generate_multi_table(struct Table *tables, struct Array indices) {
  size_t n = indices.size;

  struct TableDescriptor *descriptors = (struct TableDescriptor *) malloc(sizeof(struct TableDescriptor) * n);

  for (int i = 0; i < n; i++) {
    struct TableDescriptor descriptor = {.index=(int) indices.values[i], .table=(tables + i)};
    descriptors[i] = descriptor;
  }

  struct MultiTable result = {
      descriptors,
      n
  };

  return result;
}

void print_multi_table(struct MultiTable *multi_table) {
  if (multi_table == NULL)
    return;

  int i;

  struct TableDescriptor descriptor;
  printf("----Start printing multi-table----\n");
  for (i = 0; i < multi_table->size; i++) {
    descriptor = multi_table->tables[i];

    printf("Index: %i\n", descriptor.index);

    print_table(descriptor.table);
  }
  printf("----End printing multi-table----\n");
}

void save_multi_table_in_file(const char *path, struct MultiTable *multi_table) {
  if (multi_table == NULL || multi_table->size == 0 || multi_table->tables == NULL) {
    return;
  }

  struct Array header = multi_table->tables[0].table->headers;

  char *file_name = generate_filename("temp/write_multi_table_%li.csv");

  // Open file
  FILE *file = fopen(file_name, "w");

  if (!file) {
    return;
  }

  int i, j, index;
  // Write header
  fprintf(file, "p;");
  for (i = 0; i < header.size; i++)
    fprintf(file, ";%lf", header.values[i]);
  fprintf(file, "\n");

  // Write separator
  fprintf(file, "n;x");
  for (i = 0; i < header.size; i++)
    fprintf(file, ";");
  fprintf(file, "\n");

  struct TableDescriptor descriptor;
  for (index = 0; index < multi_table->size; index++) {
    descriptor = multi_table->tables[index];
    printf("Table descriptor #%i - %i, %p\n", index, descriptor.index, descriptor.table);

    fprintf(file, "%i", descriptor.index);

    // Write content
    for (i = 0; i < descriptor.table->columns.size; i++) {
      // Write the column
      fprintf(file, ";%lf", descriptor.table->columns.values[i]);

      // Write the rest of content
      for (j = 0; j < header.size; j++) {
        fprintf(file, ";%lf", descriptor.table->content.matrix[i][j]);
      }

      fprintf(file, "\n");
    }
  }

  // Close the file
  fclose(file);

  // Copy file with replacing
  replace_character(file_name, path, '.', ',');
}

#endif

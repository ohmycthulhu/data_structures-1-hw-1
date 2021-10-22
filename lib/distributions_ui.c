#include <stdlib.h>
#include "binomial_table.c"
#include "multi_table.c"
#include "usual_table.c"
#include "ui.c"

/**
 * Declarations
 * */
int simple_table_ui(const char* name, const char* path, int prec);

int complex_table_ui(const char* name, const char* path, int distinct_numbers, int evenly_spaced);

/**
 * Implementations
 * */
int simple_table_ui(const char* name, const char* path, int prec) {
  /**
   * The algorithm:
   *    1. Read table from normal file
   *    2. Get the row and column for this table
   *    3. Display the result
   * */
  print_start(name);

  print_message("Reading", "Started reading the table");
  struct Table table = create_table(path);

  print_message("Reading", "Finished reading the table");
  double n, m;
  read_input("Insert the index to find: ", "The index doesn't exists", &table, &n, &m, 0, prec);

  char *error = (char *) malloc(sizeof(char) * 256);
  error[0] = '\0';

  double value = get_value(table, n, m, &error);

  print_result(value, error);

  print_end(name);
  return 0;
}

int complex_table_ui(const char* name, const char* path, int distinct_numbers, int evenly_spaced) {
  /**
   * The algorithm:
   *    1. Read multitable from binomial
   *    2. Get the row and column for this table
   *    3. Display the result
   * */
  print_start(name);

  print_message("Reading", "Started reading the table");

  struct MultiTable binomial_table = create_binomial_table(path, evenly_spaced);
  print_message("Reading", "Finished reading the table");

  int iteration = read_iteration("Input iteration number: ", "Iteration does not exists", &binomial_table);

  struct Table *table = find_table(binomial_table, iteration);

  if (table == NULL) {
    print_message("Error", "Unexpected behaviour!");
    return 1;
  }

  int index;
  double d_index, precision;

  if (distinct_numbers) {
    index = read_number("Input df1");
    precision = read_number("Input df2");
  } else {
    read_input("Input searching number: ", "Number doesn't exits", table, &d_index, &precision, iteration, 0);
    index = (int) d_index;
  }

  char *error = (char *) malloc(sizeof(char) * 256);
  error[0] = '\0';

  double value = get_value(*table, index, precision, &error);

  print_result(value, error);

  print_end(name);
  return 0;
}

#include <stdlib.h>
#include "binomial_table.c"
#include "multi_table.c"
#include "usual_table.c"
#include "ui.c"

/**
 * Declarations
 * */
int simple_table_ui(const char *name, const char *path, int prec);

int simple_table_two_input_ui(
    const char *name,
    const char *path,
    const char *input_msg_1,
    const char *input_msg_2
);

int complex_table_ui(const char *name, const char *path, int evenly_spaced);

int complex_table_two_inputs_ui(
    const char *name,
    const char *path,
    const char *input_msg_1,
    const char *input_msg_2,
    int evenly_spaced
);

/**
 * Implementations
 * */
int simple_table_ui(const char *name, const char *path, int prec) {
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

int simple_table_two_input_ui(
    const char *name,
    const char *path,
    const char *input_msg_1,
    const char *input_msg_2
) {
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
  double n = read_input_value(
      input_msg_1,
      "The value is not supported",
      table.columns
  );
  double m = read_input_value(
      input_msg_2,
      "The value is not supported",
      table.headers
  );

  char *error = (char *) malloc(sizeof(char) * 256);
  error[0] = '\0';

  double value = get_value(table, n, m, &error);

  print_result(value, error);

  print_end(name);
  return 0;
}

int complex_table_ui(const char *name, const char *path, int evenly_spaced) {
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

  read_input("Input searching number: ", "Number doesn't exits", table, &d_index, &precision, iteration, 0);
  index = (int) d_index;

  char *error = (char *) malloc(sizeof(char) * 256);
  error[0] = '\0';

  double value = get_value(*table, index, precision, &error);

  print_result(value, error);

  print_end(name);
  return 0;
}

int complex_table_two_inputs_ui(
    const char *name,
    const char *path,
    const char *input_msg_1,
    const char *input_msg_2,
    int evenly_spaced
) {
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

  double input_column, input_row;
  input_column = read_input_value(input_msg_1, "Value is not supported", table->headers);
  input_row = read_input_value(input_msg_2, "Value is not supported", table->columns);

  char *error = (char *) malloc(sizeof(char) * 256);
  error[0] = '\0';

  double value = get_value(*table, input_row, input_column, &error);

  print_result(value, error);

  print_end(name);
  return 0;
}

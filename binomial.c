//
// Created by cthulhu on 14/10/2021.
//
#include "binomial_table.c"
#include "multi_table.c"
#include "ui.c"

int main(int argc, char **argv) {
  /**
   * The algorithm:
   *    1. Read multitable from binomial
   *    1.1. If argument '-p' is provided, print the content, and exit
   *    2. Get the row and column for this table
   *    3. Display the result
   * */
  print_start("Binomial distribution");

  print_message("Reading", "Started reading the table");

  struct MultiTable binomial_table = create_binomial_table("data/binomial.csv");
  print_message("Reading", "Finished reading the table");

  if (argc > 1 && strcmp(argv[1], "-p") == 0) {
    print_multi_table(&binomial_table);

    return 0;
  }

  int iteration = read_iteration("Input iteration number: ", "Iteration does not exists", &binomial_table);

  struct Table *table = find_table(binomial_table, iteration);

  if (table == NULL) {
    print_message("Error", "Unexpected behaviour!");
    exit(1);
  }

  int index;
  double d_index, precision;
  read_input("Input searching number: ", "Number doesn't exits", table, &d_index, &precision, iteration, 0);
  index = (int) d_index;

  char *error = (char *) malloc(sizeof(char) * 256);
  error[0] = '\0';

  double value = get_value(*table, index, precision, &error);

  print_result(value, error);

  print_end("Binomial distribution");
  return 0;
}

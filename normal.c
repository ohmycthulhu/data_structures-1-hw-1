#include <stdlib.h>
#include "lib/usual_table.c"
#include "lib/ui.c"

int main() {
  print_start("Normal distribution");

  print_message("Reading", "Started reading the table");
  struct Table table = create_table("data/normal.csv");

  print_message("Reading", "Finished reading the table");
  double n, m;
  read_input("Insert the index to find: ", "The index doesn't exists", &table, &n, &m, 0, 1);

  char *error = (char *) malloc(sizeof(char) * 256);
  error[0] = '\0';

  double value = get_value(table, n, m, &error);

  print_result(value, error);

  print_end("Normal distribution");
  return 0;
}

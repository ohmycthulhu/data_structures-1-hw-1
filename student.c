//
// Created by cthulhu on 19/10/2021.
//
#include "lib/ui.c"
#include "lib/distributions.c"
#include "lib/array.c"

int main() {
  print_start("Student's T Distribution");

  // Get range of integers
  double t_start, t_end;
  read_range(
    "Input df1",
    0,
    1,
    1e3,
    &t_start,
    &t_end
  );
  struct Array ts = generate_array(t_start, t_end, 10);

  // Get range of alphas
  double alpha_start, alpha_end;
  read_range(
      "Input df2",
      0,
      1,
      1e3,
      &alpha_start,
      &alpha_end
  );
  struct Array alphas = generate_array(alpha_start, alpha_end, 10);

  // Generate the table
  struct Table table = generate_t_dist_table(ts, alphas);

  // Write table into file
  char* path = (char*)malloc(sizeof(char) * 256);
  sprintf(path, "result-t-%li.csv", random());
  write_table_to_csv_file(path, table);

  // Print the content of table
  print_message("Result", "Student's T Distribution table");
  print_table(&table);

  // Print the location of file
  print_message("Result location", path);

  print_end("Student's T Distribution");
  // Return
  return 0;
}

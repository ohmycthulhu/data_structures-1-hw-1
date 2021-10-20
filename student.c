//
// Created by cthulhu on 19/10/2021.
//
#include "ui.c"
#include "distributions.c"
#include "array.c"

int main() {
  /**
   * The algorithm:
   *    1. Input
   *    1.1. Get range for t
   *    1.2. Get range for alpha
   *    2. Generate the table
   *    3. Output
   *    3.1. Display the content of table
   *    3.2. Write the table into a file
   *    3.3. Display path to the file
   * */

  print_start("Student's T Distribution");

  // Get range of integers
  double t_start, t_end;
  read_range(
    "Input t",
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
      "Input alpha",
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

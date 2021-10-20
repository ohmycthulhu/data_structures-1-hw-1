//
// Created by cthulhu on 19/10/2021.
//
#include<stdlib.h>
#include "ui.c"
#include "distributions.c"
#include "array.c"

int main() {
  /**
   * The algorithm:
   *    1. Input
   *    1.1. Get range for df1
   *    1.2. Get range for df2
   *    2. Generate the multi-table
   *    3. Output
   *    3.1. Display the content of table
   *    3.2. Write the table into a file
   *    3.3. Display path to the file
   * */
  print_start("F Distribution");

  // Get range of df_1
  double df1_start, df1_end;
  read_range(
    "Input df1",
    0,
    1,
    1e3,
    &df1_start,
    &df1_end
  );
  struct Array df1s = generate_array(df1_start, df1_end, 10);

  // Get range of df_2
  double df2_start, df2_end;
  read_range(
      "Input df2",
      0,
      1,
      1e3,
      &df2_start,
      &df2_end
  );
  struct Array df2s = generate_array(df2_start, df2_end, 10);

  // Generate the table
  struct MultiTable content = generate_f_dist_multi_table(df1s, df2s);

  // Write table into file
  char* path = (char*)malloc(sizeof(char) * 256);
  sprintf(path, "result-f-%li.csv", random());
  save_multi_table_in_file(path, &content);

  // Print the content of table
  print_message("Result", "F Distribution");
  print_multi_table(&content);

  // Print the location of file
  print_message("Result location", path);

  print_end("F Distribution");

  // Return
  return 0;
}

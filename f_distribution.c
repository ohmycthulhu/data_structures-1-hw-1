//
// Created by cthulhu on 19/10/2021.
//
#include<stdlib.h>
#include "lib/ui.c"
#include "lib/distributions.c"
#include "lib/array.c"

int main() {
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

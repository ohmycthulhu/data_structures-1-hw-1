//
// Created by cthulhu on 13/10/2021.
//
#include <stdlib.h>
#include "test_helpers.c"
#include "distributions.c"

const char *FILE_NAME = "distribution.c";

int t_dist_cum_test();

int chi_square_dist_cum_test();

int f_dist_cum_test();

int main() {
  display_test_start(FILE_NAME);

  int errors = 0;
  errors += t_dist_cum_test();
  errors += chi_square_dist_cum_test();
  errors += f_dist_cum_test();

  display_errors_count(FILE_NAME, errors);
  display_test_end(FILE_NAME);
}

int t_dist_cum_test() {
  // Function: double t_dist_cum(int degree_of_freedom, double t);
  display_test_start("t_dist_cum");

  int errors = 0;

  // t_dist_cum(4, 0.05) = 2.131847
  errors += assert_approx_equal(
      2.131847,
      t_dist_cum(4, 0.05)
  );

  // t_dist_cum(2, 0.25) = 0.816497
  errors += assert_approx_equal(
      0.816497,
      t_dist_cum(2, 0.25)
  );

  // t_dist_cum(13, 0.01) = 2.65031
  errors += assert_approx_equal(
      2.65031,
      t_dist_cum(13, 0.01)
  );

  display_test_end("t_dist_cum");

  return errors;
}

int chi_square_dist_cum_test() {
  // Function: double chi_square_dist_cum(int degree_of_freedom, double t);
  display_test_start("chi_square_dist_cum");

  int errors = 0;

  // chi_square_dist_cum(4, 0.2) = 0.7289
  errors += assert_approx_equal(
      0.7289,
      chi_square_dist_cum(4, 0.2)
  );

  // chi_square_dist_cum(20, 0.05) = 31.410
  errors += assert_approx_equal(
      31.410,
      chi_square_dist_cum(20, 0.05)
  );

  // chi_square_dist_cum(10, 0.02) = 21.161
  errors += assert_approx_equal(
      21.161,
      chi_square_dist_cum(10, 0.02)
  );

  display_test_end("chi_square_dist_cum");

  return errors;
}

int f_dist_cum_test() {
  // Function: double f_dist_cum(int degree_of_freedom_1, int degree_of_freedom_2, double alpha);
  display_test_start("f_dist_cum");

  int errors = 0;

  // f_dist_cum(4, 7, 0.1) =  2.96053
  errors += assert_approx_equal(
      2.96053,
      f_dist_cum(4, 7, 0.1)
  );

  // f_dist_cum(15, 18, 0.05) =  2.2686
  errors += assert_approx_equal(
      2.2686,
      f_dist_cum(15, 18, 0.05)
  );

  // f_dist_cum(10, 5, 0.025) = 6.6192
  errors += assert_approx_equal(
      6.6192,
      f_dist_cum(10, 5, 0.025)
  );

  display_test_end("f_dist_cum");

  return errors;
}

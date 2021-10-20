//
// Created by cthulhu on 13/10/2021.
//
#include <stdlib.h>
#include "test_helpers.c"
#include "math.c"
#include "array.c"

const char* FILE_NAME = "math_test.c";

// Function for testing:
// double lower_incomplete_gamma(double s, double x);
int lower_incomplete_gamma_test();

// Function for testing:
// double beta(double x, double y);
int beta_test();

// Function for testing:
// double incomplete_beta(double x, double a, double b);
int incomplete_beta_test();

// Function for testing:
// long factorial(int number);
int factorial_test();

int main() {
    display_test_start(FILE_NAME);
    int errors = 0;

    errors += factorial_test();
    errors += lower_incomplete_gamma_test();
    errors += beta_test();
    errors += incomplete_beta_test();

    display_errors_count(FILE_NAME, errors);
    display_test_end(FILE_NAME);
}

int lower_incomplete_gamma_test() {
    // Function: double lower_incomplete_gamma(double s, double x);
    // Start
    display_test_start("lower_incomplete_gamma");

    int errors = 0;

    errors += assert_approx_equal(
            0.6321205588285576784045,
            lower_incomplete_gamma(1, 1)
    );

    errors += assert_approx_equal(
            0.9816843611112658197063,
            lower_incomplete_gamma(1, 4)
    );

    errors += assert_approx_equal(
            1.69180673294519833651,
            lower_incomplete_gamma(0.5, 2)
    );

    // End
    display_test_end("lower_incomplete_gamma");

    return errors;
}

int beta_test() {
    // Function: double beta(double x, double y);
    // Start of test
    display_test_start("beta");

    int errors = 0;
    // B(1.5, 0.2) = 4.477609374347168810412
    errors += assert_approx_equal(
        4.477609374347168810412,
        beta(1.5, 0.2)
    );

    // B(3, 1) = 0.3333333333333333333333
    errors += assert_approx_equal(
        0.3333333333333333333333,
        beta(3, 1)
    );

    // B(1, 2) = 0.5
    errors += assert_approx_equal(
            0.5,
            beta(1, 2)
    );

    // End of test
    display_test_end("beta");

    return errors;
}

int factorial_test() {
    // Function: long factorial(int number);
    // Start
    display_test_start("factorial");
    int errors = 0;

    // 3! = 6
    errors += assert_approx_equal(
        6,
        factorial(3)
    );

    // 5! = 120
    errors += assert_approx_equal(
    120,
    factorial(5)
    );

    // 0! = 1
    assert_equal(
    1,
    factorial(0)
    );

    // End
    display_test_end("factorial");

    return errors;
}

int incomplete_beta_test() {
    // Function: double incomplete_beta(double x, double a, double b);
    // Start
    display_test_start("incomplete_beta");
    int errors = 0;

    // I(0.4, 1, 3) = 0.784
    errors += assert_approx_equal(
        0.784,
        incomplete_beta(0.4, 1, 3)
    );

    // I(0.8, 5, 1) = 0.32768
    errors += assert_approx_equal(
    0.32768,
    incomplete_beta(0.8, 5, 1)
    );

    // I(0.8, 3, 1) = 0.512
    assert_approx_equal(
    0.512,
    incomplete_beta(0.8, 3, 1)
    );

    // End
    display_test_end("incomplete_beta");

    return errors;
}

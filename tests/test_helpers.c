//
// Created by cthulhu on 13/10/2021.
//
#ifndef TEST_HELPERS_C
#define TEST_HELPERS_C
#include <math.h>
#include <stdio.h>

// Deviation in percents
#define ALLOWED_DEVIATION 2e-2

/**
 * Declarations
 * */
 /**
  * Function for asserting if two numbers are equal
  * Return 1 if there is an error
  * */
int assert_equal(double expect, double actual);

/**
 * Function for asserting if two numbers are approximately equal
 * Return 1 if there is an error
 * */
int assert_approx_equal(double expect, double actual);

/**
 * Function for displaying test start
 * */
void display_test_start(const char* test_name);

/**
 * Function for displaying test end
 * */
void display_test_end(const char* test_name);

/**
 * Function for printing test progress
 * */
void display_test_progress(const char* test_name, int iteration, int max);

/**
 * Function for displaying errors count
 * */
void display_errors_count(const char* test_name, int errors_count);

/**
 * Implementations
 * */
int assert_equal(double expect, double actual) {
    // Check if the values are equal
    short result = expect == actual;

    // Show error if not
    if (!result) {
        printf("[Error] Expected %lf, got %lf\n", expect, actual);
    }

    // Return 0 if everything is alright
    // and 1 if there is an error
    return !result;
}

int assert_approx_equal(double expect, double actual) {
    // Check if the values are equal
    short result = (fabs(expect - actual) / expect) <= ALLOWED_DEVIATION;

    // Show error if not
    if (!result) {
        printf("[Error] Expected %lf, got %lf\n", expect, actual);
    }

    // Return 0 if everything is alright
    // and 1 if there is an error
    return !result;
}

void display_test_start(const char* test_name) {
    printf("\n[Starting] %s\n", test_name);
}

void display_test_end(const char* test_name) {
    printf("\n[End] %s\n", test_name);
}

void display_errors_count(const char* test_name, int errors_count) {
    if (errors_count > 0) {
        printf("[Status] %s: Found %i errors\n", test_name, errors_count);
    } else {
        printf("[Status] %s: Found no errors\n", test_name);
    }
}

void display_test_progress(const char* test_name, int iteration, int max) {
    printf("[Progress] %s: %i / %i\n", test_name, iteration, max);
}

#endif

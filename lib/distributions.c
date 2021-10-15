//
// Created by cthulhu on 13/10/2021.
//
#ifndef DISTRIBUTIONS_C
#define DISTRIBUTIONS_C
#include <math.h>
#include "math.c"

/**
 * Declarations
 * */

/**
 * Function for computing cumulative Student's t-distribution
 * */
double t_dist_cum(int degree_of_freedom, double t);

/**
 * Function for computing cumulative chi-square distribution
 * */
double chi_square_dist_cum(int degree_of_freedom, double t);

/**
 * Function for computing cumulative f distribution
 * */
double f_dist_cum(int degree_of_freedom_1, int degree_of_freedom_2, double alpha);

/**
 * Implementation
 * */

double t_dist_cum(int degree_of_freedom, double t) {
  double x = degree_of_freedom / (t * t + degree_of_freedom);
  double back = incomplete_beta(x, degree_of_freedom / 2, 1 / 2);
  return 1 - back / 2;
}

double chi_square_dist_cum(int degree_of_freedom, double t) {
  return lower_incomplete_gamma(degree_of_freedom / 2, t / 2) / tgamma(degree_of_freedom / 2);
}

double f_dist_cum(int degree_of_freedom_1, int degree_of_freedom_2, double alpha) {
  double k = degree_of_freedom_2 / (degree_of_freedom_1 * alpha + degree_of_freedom_2);
  double back = incomplete_beta(k, degree_of_freedom_2 / 2, degree_of_freedom_1 / 2);
  return 1 - back;
}

#endif

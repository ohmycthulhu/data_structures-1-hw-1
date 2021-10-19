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
 * Function for generating table for t distribution
 * */
struct Table generate_t_dist_table(struct Array ts, struct Array alphas);

/**
 * Function for generating table for chi-square distribution
 * */
struct Table generate_chi_dist_table(struct Array ts, struct Array alphas);

/**
 * Function for generating multi-table for f distribution
 * */
struct MultiTable generate_f_dist_multi_table(struct Array df1, struct Array df2);

/**
 * Function for generating table for f distribution
 * */
struct Table generate_f_dist_table(struct Array df1, struct Array df2, double alpha);

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

struct Table generate_t_dist_table(struct Array ts, struct Array alphas) {
  int n = ts.size, m = alphas.size;
  int actual_size = 0;
  double** matrix_content = (double**)malloc(sizeof(double*) * ts.size);
  double* row;
  int prev_t = -1, curr_t;
  for (int i = 0; i < n; i++) {
    curr_t = (int)ts.values[i];
    if (curr_t == prev_t) {
      continue;
    }

    row = (double*)malloc(sizeof(double) * m);

    for (int j = 0; j < m; j++) {
      row[j] = t_dist_cum(ts.values[i], alphas.values[j]);
    }

    matrix_content[actual_size] = row;

    ++actual_size;
  }

  struct Matrix matrix = {matrix_content, actual_size, m};
  struct Table result = {ts, alphas, matrix};
  return result;
}

struct Table generate_chi_dist_table(struct Array ts, struct Array alphas) {
  int n = ts.size, m = alphas.size;
  int actual_size = 0;
  double** matrix_content = (double**)malloc(sizeof(double*) * ts.size);
  double* row;
  int prev_t = -1, curr_t;
  for (int i = 0; i < n; i++) {
    curr_t = (int)ts.values[i];
    if (curr_t == prev_t) {
      continue;
    }

    row = (double*)malloc(sizeof(double) * m);

    for (int j = 0; j < m; j++) {
      row[j] = chi_square_dist_cum(ts.values[i], alphas.values[j]);
    }

    matrix_content[actual_size] = row;

    ++actual_size;
  }

  struct Matrix matrix = {matrix_content, actual_size, m};
  struct Table result = {ts, alphas, matrix};
  return result;
}

struct MultiTable generate_f_dist_multi_table(struct Array df1, struct Array df2) {
  double alphas[] = {1, 5, 9};

  struct Table* tables = (struct Table*)malloc(sizeof(struct Table) * 3);
  struct Array indices = {alphas, 3};

  for(int i = 0; i < 3; i++) {
    tables[i] = generate_f_dist_table(df1, df2, alphas[i] / 10);
  }

  return generate_multi_table(tables, indices);
}

struct Table generate_f_dist_table(struct Array df1, struct Array df2, double alpha) {
  int n = df2.size, m = df1.size;
  double** matrix_content = (double**)malloc(sizeof(double*) * n);
  double* row;
  for (int i = 0; i < n; i++) {
    row = (double*)malloc(sizeof(double) * m);

    for (int j = 0; j < m; j++) {
      row[j] = f_dist_cum(df1.values[j], df2.values[i], alpha);
    }

    matrix_content[i] = row;
  }

  struct Matrix matrix = {matrix_content, n, m};
  struct Table result = {df2, df1, matrix};
  return result;
}

#endif

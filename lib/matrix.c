//
// Created by cthulhu on 11/10/2021.
//
#ifndef MATRIX_C
#define MATRIX_C

/**
 * Declarations
 * */

/**
 * Structure for working with matrices
 * n is count of rows
 * m is count of columns
 * */
struct Matrix {
    double** matrix;
    size_t n, m;
};

#endif

//
// Created by cthulhu on 13/10/2021.
//

#ifndef USUAL_TABLE_C
#define USUAL_TABLE_C
#include<stdio.h>
#include "table.c"

/**
 * Declarations
 * */

struct Table read_file(FILE* file);
struct Table create_table(const char*);
struct Matrix read_content(FILE* file, size_t rows, size_t columns);
struct Array read_headers(FILE* file);
struct Array read_columns(FILE* file);

/**
 * Implementation
 * */
struct Table read_file(FILE* file) {
    struct Array headers = read_headers(file);
    struct Array columns = read_columns(file);
    struct Matrix content = read_content(file, columns.size, headers.size);

    struct Table result = {
            headers,
            columns,
            content
    };

    return result;
}

struct Table create_table(const char* src) {
    static const char* tmpFile = "temp/table.csv";
    replace_character(src, tmpFile, ',', '.');
    FILE * f = fopen(tmpFile, "r");
    struct Table result = read_file(f);
    fclose(f);
    return result;
}

struct Matrix read_content(FILE* file, size_t rows, size_t columns) {
    reset_pointer(file);

    skip_line(file);

    double** content = (double**)malloc(sizeof(double*) * rows);

    double temp;
    for (int i = 0; i < rows; i++) {
        // Skip the first value
        fscanf(file, "%lf", &temp);

        // Initialize new row
        content[i] = (double*)malloc(sizeof(double) * columns);

        // Scan the row
        for (int j = 0; j < columns; j++) {
            fscanf(file, ";%lf", &temp);
            content[i][j] = temp;
        }

        // Go to the next line
        fscanf(file, "\n");
    }

    struct Matrix result = {
            content,
            rows,
            columns,
    };

    return result;
}

struct Array read_headers(FILE* file) {
    reset_pointer(file);

    size_t size = count_numbers(file) - 1;
    double * numbers = (double*)malloc(sizeof(double) * size);
    double n;

    reset_pointer(file);

    for (int i = 0; i < size; i++) {
        fscanf(file, ";");
        fscanf(file, "%lf", &n);
        numbers[i] = n;
    }

    struct Array result = {
            numbers,
            size
    };

    reset_pointer(file);

    return result;
}

struct Array read_columns(FILE* file) {
    reset_pointer(file);

    size_t n = count_lines(file) - 1;
    double* numbers = (double*)malloc(sizeof(double) * n);
    double num;

    for (int i = 0; i < n; i++) {
        count_numbers(file);
        fscanf(file, "%lf", &num);
        numbers[i] = num;
    }

    struct Array result = {
            numbers,
            n
    };

    return result;
}

#endif

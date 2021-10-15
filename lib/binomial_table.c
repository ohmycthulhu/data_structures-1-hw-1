//
// Created by cthulhu on 13/10/2021.
//
#ifndef BINOMIAL_TABLE_C
#define BINOMIAL_TABLE_C
#include "array.c"
#include "table.c"
#include "multi_table.c"
#include "file.c"

/**
 * Declarations
 * */

struct MultiTable read_binomial_table(FILE* file);
struct MultiTable create_binomial_table(const char* src);
struct Array read_headers(FILE* file);
int get_iteration_size(FILE * file);
struct Table get_iteration_content(FILE * file, struct Array headers, int iteration_size);

/**
 * Implementations
 * */
struct MultiTable read_binomial_table(FILE* file) {
    // Get headers
    struct Array headers = read_headers(file);

    // Skip 2 lines
    skip_line(file);
    skip_line(file);

    // Count the iterations count
    // And collect indices array
    int iteration_size;
    struct Array indices = {NULL, 0};

    while ((iteration_size = get_iteration_size(file)) > 0) {
        get_iteration_content(file, headers, iteration_size + 1);
        add_to_array(&indices, iteration_size);
    }

    // Reset to the start and skip header lines
    reset_pointer(file);
    skip_line(file);
    skip_line(file);

    // Get the iteration size
    struct Table* contents = (struct Table*)malloc(sizeof(struct Table) * indices.size);

    for (int i = 0; i < indices.size; i++) {
        contents[i] = get_iteration_content(file, headers, indices.values[i] + 1);
    }

    return generate_multi_table(contents, indices);
}

struct MultiTable create_binomial_table(const char* src) {
    // Create intermediate file
    replace_character(src, "temp/binomial.csv", ',', '.');

    // Open file
    FILE* file = fopen("temp/binomial.csv", "r");

    // Get the result
    struct MultiTable result = read_binomial_table(file);

    // Close file
    fclose(file);

    return result;
}

struct Array read_headers(FILE* file) {
    reset_pointer(file);

    int size = count_numbers(file) - 2;
    double * numbers = (double*)malloc(sizeof(double) * size);

    reset_pointer(file);

    // Skip the p;; in beginning
    fscanf(file, "p;");

    // Read every number ;{number}
    for (int i = 0; i < size; i++) {
        fscanf(file, ";%lf", numbers + i);
    }

    reset_pointer(file);

    struct Array result = {
        numbers,
        size
    };

    return result;
}

int get_iteration_size(FILE * file) {
    static int prevResult;
    int result = 0;
    fscanf(file, "%i", &result);
    if (prevResult == result) {
        return 0;
    }
    prevResult = result;
    return result;
}

struct Table get_iteration_content(FILE * file, struct Array headers, int iteration_size) {
    double* columns_data = (double*)malloc(sizeof(double) * iteration_size);

    double** content_values = (double**)malloc(sizeof(double*) * iteration_size);

    int t;
    for (int i = 0; i < iteration_size; i++) {
        if (i == 0) {
            fscanf(file, "%i;", &t);
        } else {
            fscanf(file, ";");
        }
        fscanf(file, "%lf", columns_data + i);

        content_values[i] = (double*) malloc(sizeof(double) * headers.size);
        for (int j = 0; j < headers.size; j++) {
            fscanf(file, ";%lf", content_values[i] + j);
        }

        skip_line(file);
    }

    struct Matrix content = {.matrix=content_values, .n=iteration_size, .m=headers.size};
    struct Array columns = {.values=columns_data, .size=iteration_size};

    struct Table result = {headers, columns, content};

    return result;
}

#endif

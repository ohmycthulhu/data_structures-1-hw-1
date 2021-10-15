#ifndef TABLE_C
//
// Created by cthulhu on 11/10/2021.
//
#define TABLE_C
#include <string.h>
#include "array.c"
#include "file.c"
#include "matrix.c"

/**
 * Declarations
 * */

struct Table {
    struct Array headers;
    struct Array columns;
    struct Matrix content;
};

double get_value(struct Table table, double n, double m, char** error);
void write_table_to_file(struct Table table, const char* src);
void print_table(struct Table *table);

/**
 * Implementation
 * */

double get_value(struct Table table, double n, double m, char** error) {
    int i = find_index(table.columns, n);
    int j = find_index(table.headers, m);

    if (i < 0 || j < 0) {
        printf("Couldn't find something\n%i , %i\n", i, j);
        if (error != NULL) {
            *error = "Some of value doesn't exist";
        }
        return -1;
    }

    return table.content.matrix[i][j];
}

void write_table_to_file(struct Table table, const char* src) {
    FILE* file = fopen(src, "w");

    if (ferror(file)) {
        printf("Couldn't open a file");
        return;
    }

    // Write table headers
    for (int i = 0; i < table.headers.size; ++i) {
        fprintf(file, ";%lf", table.headers.values[i]);
    }

    fprintf(file, "\n");

    // Write table content
    for (int i = 0; i < table.columns.size; ++i) {
        // Print column
        fprintf(file, "%lf", table.columns.values[i]);

        // Print matrix content
        for (int j = 0; j < table.content.m; ++j) {
            fprintf(file, ";%lf", table.content.matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void print_table(struct Table *table) {
    if (table == NULL)
        return;

    int i, j;

    // Print the header
    for (i = 0; i < table->headers.size; i++) {
        printf("\t");
        printf("%lf", table->headers.values[i]);
    }
    printf("\n");

    // Print the rows
    for (i = 0; i < table->columns.size; i++) {
        // Print the first column
        printf("%lf", table->columns.values[i]);

        // Print the rest
        for (j = 0; j < table->headers.size; j++) {
            printf("\t%lf", table->content.matrix[i][j]);
        }
        printf("\n");
    }
}

#endif

//
// Created by cthulhu on 11/10/2021.
//
#ifndef FILE_C
#define FILE_C
#include <stdio.h>

/**
 * Declarations
 * */

void skip_line(FILE* file);
void reset_pointer(FILE *file);
int count_numbers(FILE* f);
int count_lines(FILE* f);
void replace_character(const char*, const char*, char search, char replace);
void print_curr_characters(FILE* file, size_t count);

/**
 * Implementation
 * */

int count_numbers(FILE* f) {
    int result = 1, c;
    while ((c = getc(f)) != '\n' && c != EOF) {
        if (c == ';')
            result += 1;
    }
    return result;
}

int count_lines(FILE* f) {
    reset_pointer(f);

    int c, result = 0;
    while ((c = getc(f)) != EOF) {
        if (c == '\n')
            result += 1;
    }

    reset_pointer(f);

    return result;
}

void skip_line(FILE* file) {
    int c;
    while ((c = getc(file)) != '\n' && c != EOF);
}

void reset_pointer(FILE *file) {
    fseek(file, 0, SEEK_SET);
}

void replace_character(const char* file, const char* dest, char search, char replace) {
    FILE * f = fopen(file, "r");
    FILE * out = fopen(dest, "w");

    int c;
    while ((c = getc(f)) != EOF) {
        putc(c != search ? c : replace, out);
    }

    fclose(f);
    fclose(out);
}

void print_curr_characters(FILE* file, size_t count) {
    for(int i = 0; i < count; i++)
        printf("%c", getc(file));
    printf("\n\n");
    fseek(file, -(long)count, SEEK_CUR);
}

#endif

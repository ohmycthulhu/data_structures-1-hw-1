//
// Created by cthulhu on 11/10/2021.
//
#ifndef FILE_C
#define FILE_C
#include <stdio.h>
#include <stdlib.h>

/**
 * This file contains functions for working with FILE* and entire files
 * */

/**
 * Declarations
 * */

/**
 * Function for skipping the current line
 * */
void skip_line(FILE* file);

/**
 * Function for resetting the pointer to start of the file
 * */
void reset_pointer(FILE *file);

/**
 * Function that counts on the line by counting amount of ; and also moves the pointer to the end of line
 * */
int count_numbers(FILE* f);

/**
 * Function for counting the lines in file
 * */
int count_lines(FILE* f);

/**
 * Function that creates new file from source and replaces `search` character by `replace`
 * */
void replace_character(const char*, const char*, char search, char replace);

/**
 * Function for printing n characters from current position of pointer
 * Used primarily for debugging
 * Reset the pointer to the state where it was, when the function was called
 * */
void print_curr_characters(FILE* file, size_t count);

/**
 * Function for generating random filenames
 * */
char* generate_filename(const char* format);

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

    if (f == NULL) {
      printf("[Error] Couldn't open file %s\n", file);
      exit(1);
    }

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

char* generate_filename(const char* format) {
  char* path = (char*)malloc(sizeof(char) * 256);
  sprintf(path, format, random());
  return path;
}

#endif

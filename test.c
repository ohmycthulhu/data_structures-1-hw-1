//
// Created by cthulhu on 14/10/2021.
//
#include "lib/binomial_table.c"

int main() {
    const char* src = "data/binomial.csv";

    // Create intermediate file
    replace_character(src, "temp/binomial.csv", ',', '.');

    // Open file
    FILE* file = fopen("temp/binomial.csv", "r");

    // Get the result
    struct Array header = read_headers(file);

    printf("File header:\n");
    print_array(&header);

    printf("Adding 1.1 to header\n");
    add_to_array(&header, 1.1);
    print_array(&header);

    return 0;
}

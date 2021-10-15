#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lib/usual_table.c"

void read_value(const char*, struct Table, double*, double*);

int main() {
    struct Table table = create_table("data/normal.csv");

    double n, m;
    read_value("Insert the index to find: ", table, &n, &m);

    char* error = (char*)malloc(sizeof(char) * 256);
    error[0] = '\0';

    double value = get_value(table, n, m, &error);

    if (strlen(error)) {
        printf("%s\n", error);
    } else {
        printf("Value is %lf\n", value);
    }

    write_table_to_file(table, "temp/r.csv");
    replace_character("temp/r.csv", "temp/f.csv", '.', ',');

    return 0;
}

void read_value(const char* msg, struct Table table, double* n, double* m) {
    double temp;
    while(1) {
        // Print the message and get input
        printf("%s", msg);
        scanf("%lf", &temp);

        // Transform the input into column and header numbers
        *n = floor(temp * 10) / 10;
        *m = ((int)(temp * 100) % 10) / 1e2;
        if (find_index(table.columns, *n) != -1 && find_index(table.headers, *m) != -1)
            break;
    }
}

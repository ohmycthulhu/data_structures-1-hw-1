//
// Created by cthulhu on 13/10/2021.
//
#ifndef MULTI_TABLE_C
#define MULTI_TABLE_C
#include "table.c"

/**
 * Declarations
 * */

struct TableDescriptor {
    int index;
    Table* table;
};

struct MultiTable{
    struct TableDescriptor* tables;
    size_t size;
};

struct Table* find_table(struct MultiTable multiTable, int index);
struct MultiTable generate_multi_table(struct Table* tables, struct Array indices);
void print_multi_table(struct MultiTable* multi_table);

/**
 * Implementations
 * */
struct Table* find_table(struct MultiTable multiTable, int index) {
    for (int i = 0; i < multiTable.size; i++) {
        if (multiTable.tables[i].index == index) {
            return multiTable.tables[i].table;
        }
    }

    return NULL;
}

struct MultiTable generate_multi_table(struct Table* tables, struct Array indices) {
    size_t n = indices.size;

    struct TableDescriptor* descriptors = (struct TableDescriptor*)malloc(sizeof(struct TableDescriptor*) * n);

    for (int i = 0; i < n; i++) {
        struct TableDescriptor descriptor = { .index=(int)indices.values[i], .table=(tables + i) };
        descriptors[i] = descriptor;
    }
    struct MultiTable result = {
        descriptors,
        n
    };

    return result;
}

void print_multi_table(struct MultiTable* multi_table) {
    if (multi_table == NULL)
        return;

    int i;

    struct TableDescriptor descriptor;
    printf("----Start printing multi-table----\n");
    for (i = 0; i < multi_table->size; i++) {
        descriptor = multi_table->tables[i];

        printf("Index: %i\n", descriptor.index);

        print_table(descriptor.table);
    }
    printf("----End printing multi-table----\n");
}

#endif

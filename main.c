//
// Created by cthulhu on 22/10/2021.
//
#include <stdlib.h>
#include <ctype.h>
#include "distributions_ui.c"
#include "ui.c"

enum Distribution {
    NORMAL_DISTRIBUTION,
    T_DISTRIBUTION,
    CHI_DISTRIBUTION,
    BINOMIAL_DISTRIBUTION,
    F_DISTRIBUTION,
};

/**
 * Operations for normal distribution
 * */
int normal();

/**
 * Operations for chi distribution
 * */
int chi();

/**
 * Operations for Student's T distribution
 * */
int t();

/**
 * Operations for binomial distribution
 * */
int binomial();

/**
 * Operations for normal distribution
 * */
int f();

/**
 * Print available distributions
 * */
void print_available();

/**
 *  Get the value for distribution
 * */
enum Distribution get_distribution();

/**
 * Read if user wishes to repeat
 * */
int get_repeat();

int main() {
  print_start("Main Application");

  int repeat = 0;

  do {
    printf("\n\n\n");
    enum Distribution dist = get_distribution();

    switch (dist) {
      case NORMAL_DISTRIBUTION: normal(); break;
      case CHI_DISTRIBUTION: chi(); break;
      case T_DISTRIBUTION: t(); break;
      case BINOMIAL_DISTRIBUTION: binomial(); break;
      case F_DISTRIBUTION: f(); break;
    }

    repeat = get_repeat();
  } while(repeat);

  print_end("Main Application");
  return 1;
}

int normal() {
  return simple_table_ui("Normal distribution", "data/normal.csv", 1);
}

int chi() {
  return simple_table_ui("Chi-square distribution", "data/chi.csv", 0);
}

int t() {
  return simple_table_ui("Student's T distribution", "data/t.csv", 0);
}

int binomial() {
  return complex_table_ui("Binomial distribution", "data/binomial.csv", 0, 0);
}

int f() {
  return complex_table_ui("F distribution", "data/f.csv", 1, 1);
}

/**
 * Print available distributions
 * */
void print_available() {
  print_message("Info", "Available distributions");
  print_message("Distribution", "1 - Normal Distribution");
  print_message("Distribution", "2 - Binomial Distribution");
  print_message("Distribution", "3 - Student's T Distribution");
  print_message("Distribution", "4 - Chi-square Distribution");
  print_message("Distribution", "5 - F Distribution");
}

/**
 *  Get the value for distribution
 * */
enum Distribution get_distribution() {
  print_available();
  int dist_index = 0;
  do {
    printf("[Input] Input the index of distribution: ");
    scanf("%i", &dist_index);

    switch (dist_index) {
      case 1: return NORMAL_DISTRIBUTION;
      case 2: return BINOMIAL_DISTRIBUTION;
      case 3: return T_DISTRIBUTION;
      case 4: return CHI_DISTRIBUTION;
      case 5: return F_DISTRIBUTION;
    }
  } while(1);
}

/**
 * Read if user wishes to repeat
 * */
int get_repeat() {
  char* inp = (char*)malloc(sizeof(char) * 256);
  char answer;
  while (1) {
    print_message("Input", "Would you like to repeat? (y/n)");
    scanf("%s", inp);
    answer = tolower(inp[0]);
    if (answer == 'y')
      return 1;
    if (answer == 'n')
      return 0;
  }
}

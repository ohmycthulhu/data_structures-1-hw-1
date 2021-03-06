//
// Created by cthulhu on 18/10/2021.
//
#ifndef UI_C
#define UI_C
#include <math.h>
#include "multi_table.c"
#include "table.c"
#include "array.c"

/**
 * Declarations
 * */

/**
 * Function for inputting the iteration number
 * The number is validated by the presence as table index in multi-table
* */
int read_iteration(const char*, const char*, struct MultiTable*);

/**
 * Function for inputting a number that is divided in two complimentary numbers
 * Precision controls the amount of digits after period
 * The result is written into double pointers
* */
void read_input(const char*, const char*, struct Table*, double*, double*, int, int);

/**
 * Function for reading number constrained by existence in array
 * */
double read_input_value(const char*, const char*, struct Array);

/**
 * Function to input double number
 * */
double read_number(const char* msg);

/**
 * Prints the start of program
 * */
void print_start(const char* msg);

/**
 * Prints the end of program
 * */
void print_end(const char* msg);

/**
 * Prints the message that has some type
 * */
void print_message(const char* type, const char* message);

/**
 * Function for reading range
 * Uses precision to narrow the number and limits to validate the range
 * Also provides the method to return and re-input the minimum
 * */
void read_range(const char*, int, double, double, double*, double*);

/**
 * Implementation
 * */

int read_iteration(const char* msg, const char* msg_fail, struct MultiTable* data) {
  if (data == NULL)
    return 0;

  int index;
  char* input = (char*)malloc(sizeof(char) * 256);
  int show_error = 0;

  do {
    if (show_error)
      print_message("Error", msg_fail);
    printf("[Input]: %s", msg);
    scanf("%s", input);
    index = atoi(input);
    show_error = 1;
  } while(index > 0 && find_table(*data, index) == NULL);

  return index;
}

void read_input(const char* msg, const char* msg_fail, struct Table* content, double* index_ptr, double* precision_ptr, int iteration, int prec) {
  if (content == NULL)
    return;

  double n, precision, index;
  double base = pow(10, prec);
  int show_error = 0;
  do {
    if (show_error)
      print_message("Error", msg_fail);
    printf("[Input]: %s", msg);
    scanf("%lf", &n);

    index = floor(n * base) / base;
    precision = n - index;
    show_error = 1;
  } while((iteration > 0 && index > iteration) || get_value(*content, index, precision, NULL) == -1);

  *index_ptr = index;
  *precision_ptr = precision;
}

void print_start(const char* msg) {
  printf("---------Starting---------\n");
  print_message("Start", msg);
}

void print_end(const char* msg) {
  print_message("End", msg);
  printf("---------End---------\n");
}

void print_message(const char* type, const char* message) {
  printf("[%s] %s\n", type, message);
}

void print_result(double value, const char* error){
  if (strlen(error)) {
    print_message("Error", error);
  } else {
    char* buffer = (char*) malloc(sizeof(char) * 256);
    sprintf(buffer, "Value is %lf", value);
    print_message("Result", buffer);
  }
}

void read_range(const char* msg, int prec, double start, double end, double* output_start, double* output_end) {
  double s = -1, e = -1;
  char* str = (char*)malloc(sizeof(char) * 256);
  char* error = "";
  double base = pow(10, prec);
  do {
    do {
      if (strlen(error)) {
        print_message("Error", error);
        free(error);
      }
      error = (char *) malloc(sizeof(char) * 256);
      error[0] = '\0';
      printf("[Input] %s (lowest): ", msg);
      scanf("%s", str);
      s = floor(strtod(str, &error) * base) / base;
    } while (s < start || strlen(error) > 0);

    do {
      if (strlen(error)) {
        print_message("Error", error);
        free(error);
      }
      error = (char *) malloc(sizeof(char) * 256);
      error[0] = '\0';
      printf("[Input] %s (highest) (r to return): ", msg);
      scanf("%s", str);
      if (strcmp(str, "r") == 0) {
        e = end;
        s = start - 1;
      } else {
        e = floor(strtod(str, &error) * base) / base;
      }
    } while (e > end || strlen(error) > 0);
  } while(s < start);

  *output_start = s;
  *output_end = e;
}

double read_number(const char* msg) {
  char* str = (char*)malloc(sizeof(char) * 256),
      *error = (char*)malloc(sizeof(char) * 256);
  double res;
  do {
    error[0] = '\0';
    printf("[Input] %s: ", msg);
    scanf("%s", str);

    res = strtod(str, &error);
  } while(error[0] != '\0');

  free(str);
  return res;
}

double read_input_value(const char* msg, const char* error, struct Array array) {
  double result;
  do {
    result = read_number(msg);
    if (exists_in_array(array, result)) {
      break;
    }
    print_message("Error", error);
    print_message("Info", "Available values:");
    print_array(&array);
  } while(1);
  return result;
}

#endif

//
// Created by cthulhu on 13/10/2021.
//
#ifndef CUSTOM_MATH_C
#define CUSTOM_MATH_C
#include <math.h>
#include "array.c"

#define STOP 1.0e-8
#define TINY 1.0e-30

/**
 * Declarations
 * */

/**
 * Function for computing Kummer's function
 * */

/**
 * Function for computing incomplete gamma function
 */
double lower_incomplete_gamma(double s, double x);

/***
 * Function for computing beta function
 * */
double beta(double x, double y);

/***
 * Function for computing incomplete beta function
 * */
double incomplete_beta(double x, double a, double b);

/**
 * Function for computing factorial
 * */
long factorial(int number);

/**
 * Implementation
 * */

long factorial(int number) {
    if (number <= 1) return 1;

    long result = 1;
    while(number > 1) {
        result *= number--;
    }
    return result;
}

double lower_incomplete_gamma(double s, double x) {
    double sum = 0, next = STOP *  2;
    double f, sec;

    for (int i = 0; i < 30; ++i) {
        f = (i % 2 == 0 ? 1 : -1) / (double)factorial(i);
        sec = pow(x, s + i) / (s + i);
        next = f * sec;
        sum += next;
    }

    return sum;
}

double beta(double x, double y) {
    return (tgamma(x) * tgamma(y)) / tgamma(x + y);
}

double incomplete_beta(double x, double a, double b) {
    if (x < 0.0 || x > 1.0) return 1.0/0.0;

    /*The continued fraction converges nicely for x < (a+1)/(a+b+2)*/
    if (x > (a+1.0)/(a+b+2.0)) {
        return (1.0-incomplete_beta(1-x,b,a)); /*Use the fact that beta is symmetrical.*/
    }

    /*Find the first part before the continued fraction.*/
    const double lbeta_ab = lgamma(a)+lgamma(b)-lgamma(a+b);
    const double front = exp(log(x)*a+log(1.0-x)*b-lbeta_ab) / a;

    /*Use Lentz's algorithm to evaluate the continued fraction.*/
    double f = 1.0, c = 1.0, d = 0.0;

    int i, m;
    for (i = 0; i <= 200; ++i) {
        m = i/2;

        double numerator;
        if (i == 0) {
            numerator = 1.0; /*First numerator is 1.0.*/
        } else if (i % 2 == 0) {
            numerator = (m*(b-m)*x)/((a+2.0*m-1.0)*(a+2.0*m)); /*Even term.*/
        } else {
            numerator = -((a+m)*(a+b+m)*x)/((a+2.0*m)*(a+2.0*m+1)); /*Odd term.*/
        }

        /*Do an iteration of Lentz's algorithm.*/
        d = 1.0 + numerator * d;
        if (fabs(d) < TINY) d = TINY;
        d = 1.0 / d;

        c = 1.0 + numerator / c;
        if (fabs(c) < TINY) c = TINY;

        const double cd = c*d;
        f *= cd;

        /*Check for stop.*/
        if (fabs(1.0-cd) < STOP) {
            return front * (f-1.0);
        }
    }

    return 1.0/0.0;
}

#endif

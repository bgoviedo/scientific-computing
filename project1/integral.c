//  project1
//
//  Created by Bijan Oviedo on 9/27/16.
//  Copyright © 2016 Bijan Oviedo. All rights reserved.
//

#include <stdio.h>
#include <math.h>

#define MINLEVEL 0
#define MAXLEVEL 30

// define your function here
double f(double x) {
    return x*x;
}

// calculates the area of trapezoid from x = a to x = b along the function f
double fine_approximation(double a, double b, double (*f)(double)) {
    return (f(a) + f(b)) * ((b - a) / 2);
}

// finds the integral of function f from x = a to x = b with tolerance tol using the adaptive trapezoidal rule
double integrate(double (*f)(double), double a, double b, double tol, int level) {
    double midpoint = (a + b) / 2;
    
    double approximation1 = fine_approximation(a, midpoint, f);
    double approximation2 = fine_approximation(midpoint, b, f);
    
    int break_condition1 = (level >= MINLEVEL) && (fabs(approximation1 - approximation2) <= 3 * tol);
    int break_condition2 = level >= MAXLEVEL;
    
    if (break_condition1 || break_condition2) {
        return approximation1 + approximation2;

    } else {
        return integrate(f,a, midpoint, tol/2, level + 1) + integrate(f, midpoint, b, tol/2, level + 1);
    }
}

int main() {
    
    // alter these values to determine answer
    double a = 0;
    double b = 2;
    double tolerance = 0.01;
    double (*function)(double) = &f;
    
    double integral_value = integrate(function,a,b,tolerance, 0);
    printf("The integral of the function from %lf to %lf with tolerance %lf is %lf\n\n", a, b, tolerance, integral_value);
    
    return 0;
}

#ifndef MATRIX_DOT_H
#define MATRIX_DOT_H

#include <stdio.h>
#include <stdlib.h>

#define MAX(X, Y) ((X) >= (Y) ? (X) : (Y))
#define ABS(X) (MAX(-1.0 * (X), (X)))

void allocate(double*** X, int n);
void deallocate(double*** X, int n);
void prettyprint(char* label, double** X, int n);
void matrixsum(double** X, double** Y, double*** R, int n);
void scalarproduct(double c, double** X, double*** R, int n);
void matrixproduct(double** X, double** Y, double*** R, int n);
double decompose(double** A, double*** P, double*** L, double*** U, int n);

#endif

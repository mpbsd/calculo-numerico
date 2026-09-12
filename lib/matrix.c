#include "matrix.h"

void allocate(double*** X, int n)
{
  int i;

  *X = malloc(n * sizeof(double*));

  for (i = 0; i <= n - 1; i++) {
    (*X)[i] = malloc(n * sizeof(double));
  }
}

void deallocate(double*** X, int n)
{
  int i;

  for (i = 0; i <= n - 1; i++) {
    free((*X)[i]);
  }

  free(*X);
}

void prettyprint(char* label, double** X, int n)
{
  int i;
  int j;

  printf("\n%s: \n", label);

  for (i = 0; i <= n - 1; i++) {
    for (j = 0; j <= n - 1; j++) {
      printf("%s%+12.6f%s", (j == 0) ? "[" : " ",
          X[i][j], (j == n - 1) ? "]\n" : " ");
    }
  }
}

void matrixsum(double** X, double** Y, double*** R, int n)
{
  int i;
  int j;

  for (i = 0; i <= n - 1; i++) {
    for (j = 0; j <= n - 1; j++) {
      (*R)[i][j] = X[i][j] + Y[i][j];
    }
  }
}

void scalarproduct(double c, double** X, double*** R, int n)
{
  int i;
  int j;

  for (i = 0; i <= n - 1; i++) {
    for (j = 0; j <= n - 1; j++) {
      (*R)[i][j] = c * X[i][j];
    }
  }
}

void matrixproduct(double** X, double** Y, double*** R, int n)
{
  int i;
  int j;
  int k;

  for (i = 0; i <= n - 1; i++) {
    for (j = 0; j <= n - 1; j++) {
      (*R)[i][j] = 0;
      for (k = 0; k <= n - 1; k++) {
        (*R)[i][j] += X[i][k] * Y[k][j];
      }
    }
  }
}

double decompose(double** A, double*** P, double*** L, double*** U, int n)
{
  int i;
  int j;
  int k;
  int p;
  int* pivot = NULL;
  double** B = NULL;
  double d = 1.0;
  double m;
  double r;
  double t;

  pivot = malloc(n * sizeof(int));
  allocate(&B, n);

  for (i = 0; i <= n - 1; i++) {
    pivot[i] = i;
    for (j = 0; j <= n - 1; j++) {
      B[i][j] = A[i][j];
    }
  }

  for (j = 0; j <= n - 1; j++) {
    p = j;
    m = ABS(B[j][j]);
    for (k = j + 1; k <= n - 1; k++) {
      if (ABS(B[k][j]) > m) {
        m = ABS(B[k][j]);
        p = k;
      }
    }
    if (p != j) {
      for (k = 0; k <= n - 1; k++) {
        t = B[j][k];
        B[j][k] = B[p][k];
        B[p][k] = t;
      }
      i = pivot[j];
      pivot[j] = pivot[p];
      pivot[p] = i;
      d *= -1.0;
    }
    d *= B[j][j];
    if (ABS(B[j][j]) != 0) {
      r = 1.0 / B[j][j];
      for (i = j + 1; i <= n - 1; i++) {
        m = B[i][j] * r;
        B[i][j] = m;
        for (k = j + 1; k <= n - 1; k++) {
          B[i][k] = B[i][k] - m * B[j][k];
        }
      }
    }
  }

  for (i = 0; i <= n - 1; i++) {
    for (j = 0; j <= n - 1; j++) {
      (*P)[i][j] = (i == pivot[j]) ? 1.0 : 0.0;
      if (i <= j) {
        (*L)[i][j] = (i == j) ? 1.0 : 0.0;
        (*U)[i][j] = B[i][j];
      } else {
        (*L)[i][j] = B[i][j];
        (*U)[i][j] = 0.0;
      }
    }
  }

  free(pivot);
  deallocate(&B, n);

  return d;
}

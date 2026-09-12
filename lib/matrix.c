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

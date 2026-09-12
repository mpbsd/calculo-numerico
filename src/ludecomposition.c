#include <stdio.h>
#include <stdlib.h>

#define MAX(X, Y) ((X) >= (Y) ? (X) : (Y))
#define ABS(X) (MAX(-1.0 * (X), (X)))

void allocate(double*** X, int n);
void deallocate(double*** X, int n);
void prettyprint(char* label, double** X, int n);
double decompose(double*** A, double*** P, double*** L, double*** U, int n);
void multiply(double** X, double** Y, double*** R, int n);

int main(void) {
  int N = 3;
  double** A = NULL;
  double** P = NULL;
  double** L = NULL;
  double** U = NULL;
  double** R = NULL;
  double detA;

  allocate(&A, N);
  allocate(&P, N);
  allocate(&L, N);
  allocate(&U, N);
  allocate(&R, N);

  A[0][0] = 1.0;
  A[0][1] = 2.0;
  A[0][2] = 3.0;
  A[1][0] = 4.0;
  A[1][1] = 5.0;
  A[1][2] = 6.0;
  A[2][0] = 7.0;
  A[2][1] = 8.0;
  A[2][2] = 9.0;

  prettyprint("A", A, N);

  detA = decompose(&A, &P, &L, &U, N);

  prettyprint("P", P, N);
  prettyprint("L", L, N);
  prettyprint("U", U, N);

  printf("\ndet(A) = %+10.6f\n", detA);

  multiply(L, U, &R, N);

  prettyprint("LU", R, N);

  deallocate(&A, N);
  deallocate(&P, N);
  deallocate(&L, N);
  deallocate(&U, N);
  deallocate(&R, N);

  exit(EXIT_SUCCESS);
}

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

double decompose(double*** A, double*** P, double*** L, double*** U, int n)
{
  int i;
  int j;
  int k;
  int p;
  int* pivot = NULL;
  double d = 1.0;
  double m;
  double r;
  double t;

  pivot = malloc(n * sizeof(int));

  for (i = 0; i <= n - 1; i++) {
    pivot[i] = i;
  }

  for (j = 0; j <= n - 1; j++) {
    p = j;
    m = ABS((*A)[j][j]);
    for (k = j + 1; k <= n - 1; k++) {
      if (ABS((*A)[k][j]) > m) {
        m = ABS((*A)[k][j]);
        p = k;
      }
    }
    if (p != j) {
      for (k = 0; k <= n - 1; k++) {
        t = (*A)[j][k];
        (*A)[j][k] = (*A)[p][k];
        (*A)[p][k] = t;
      }
      i = pivot[j];
      pivot[j] = p;
      pivot[p] = i;
      d *= -1.0;
    }
    d *= (*A)[j][j];
    if (ABS((*A)[j][j]) != 0) {
      r = 1.0 / (*A)[j][j];
      for (i = j + 1; i <= n - 1; i++) {
        m = (*A)[i][j] * r;
        (*A)[i][j] = m;
        for (k = j + 1; k <= n - 1; k++) {
          (*A)[i][k] = (*A)[i][k] - m * (*A)[j][k];
        }
      }
    }
  }

  printf("\n");
  for (i = 0; i <= n - 1; i++) {
    printf("\t%2d", pivot[i]);
  }
  printf("\n");

  for (i = 0; i <= n - 1; i++) {
    for (j = 0; j <= n - 1; j++) {
      (*P)[i][j] = (i == pivot[j]) ? 1.0 : 0.0;
      if (i <= j) {
        (*L)[i][j] = (i == j) ? 1.0 : 0.0;
        (*U)[i][j] = (*A)[i][j];
      } else {
        (*L)[i][j] = (*A)[i][j];
        (*U)[i][j] = 0.0;
      }
    }
  }

  free(pivot);

  return d;
}

void multiply(double** X, double** Y, double*** R, int n)
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

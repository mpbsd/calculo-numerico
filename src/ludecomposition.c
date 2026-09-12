#include "matrix.h"

#define MAX(X, Y) ((X) >= (Y) ? (X) : (Y))
#define ABS(X) (MAX(-1.0 * (X), (X)))

double decompose(double** A, double*** P, double*** L, double*** U, int n);

int main(void)
{
  int N = 4;
  double** A = NULL;
  double** P = NULL;
  double** L = NULL;
  double** U = NULL;
  double** R = NULL;
  double** S = NULL;
  double detA;

  allocate(&A, N);
  allocate(&P, N);
  allocate(&L, N);
  allocate(&U, N);
  allocate(&R, N);
  allocate(&S, N);

  A[0][0] =  4.0;
  A[0][1] = -1.0;
  A[0][2] =  0.0;
  A[0][3] = -1.0;
  A[1][0] =  1.0;
  A[1][1] = -2.0;
  A[1][2] =  1.0;
  A[1][3] =  0.0;
  A[2][0] =  0.0;
  A[2][1] =  4.0;
  A[2][2] = -4.0;
  A[2][3] =  1.0;
  A[3][0] =  5.0;
  A[3][1] =  0.0;
  A[3][2] =  5.0;
  A[3][3] = -1.0;

  prettyprint("A", A, N);

  detA = decompose(A, &P, &L, &U, N);

  printf("\ndet(A) = %+10.6f\n", detA);

  prettyprint("P", P, N);
  prettyprint("L", L, N);
  prettyprint("U", U, N);

  matrixproduct(L, U, &R, N);
  matrixproduct(P, R, &S, N);
  scalarproduct(-1.0, S, &R, N);
  matrixsum(A, R, &S, N);

  prettyprint("A-PLU", S, N);

  deallocate(&A, N);
  deallocate(&P, N);
  deallocate(&L, N);
  deallocate(&U, N);
  deallocate(&R, N);
  deallocate(&S, N);

  exit(EXIT_SUCCESS);
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

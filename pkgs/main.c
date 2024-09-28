#include <stdio.h>
#include <stdlib.h>

#define ABS(X) ((X >= 0) ? (X) : (-X))
#define MAX(X, Y) ((X >= Y) ? (X) : (Y))
#define N 3

void allocate(double ***);
void setfree(double **);
void init(double **, double **, double **, double **);
void display(double **, char *);
void plu(double **, double **, double **);

int main(void) {
  double **A = NULL;
  double **P = NULL;
  double **L = NULL;
  double **U = NULL;

  allocate(&A);
  allocate(&P);
  allocate(&L);
  allocate(&U);

  A[0][0] = 1.0;
  A[0][1] = -3.0;
  A[0][2] = 2.0;
  A[1][0] = -2.0;
  A[1][1] = 8.0;
  A[1][2] = -1.0;
  A[2][0] = 4.0;
  A[2][1] = -6.0;
  A[2][2] = 5.0;

  init(A, P, L, U);

  plu(P, L, U);

  display(A, "A");
  display(P, "P");
  display(L, "L");
  display(U, "U");

  setfree(A);
  setfree(P);
  setfree(L);
  setfree(U);

  exit(EXIT_SUCCESS);
}

void allocate(double ***A) { /*{{{*/
  int i = 0;

  *A = malloc(N * sizeof(malloc(N * sizeof(double))));

  for (i = 0; i < N; ++i) {
    (*A)[i] = malloc(N * sizeof(double));
  }
} /*}}}*/

void setfree(double **A) { /*{{{*/
  int i = 0;

  for (i = 0; i < N; ++i) {
    free(A[i]);
  }

  free(A);
} /*}}}*/

void init(double **A, double **P, double **L, double **U) { /*{{{*/
  int i = 0;
  int j = 0;

  for (i = 0; i < N; ++i) {
    for (j = 0; j < N; ++j) {
      P[i][j] = (i == j) ? 1.0 : 0.0;
      L[i][j] = (i == j) ? 1.0 : 0.0;
      U[i][j] = A[i][j];
    }
  }
} /*}}}*/

void display(double **A, char *label) { /*{{{*/
  int i = 0;
  int j = 0;

  printf("\n%s: \n", label);

  for (i = 0; i < N; ++i) {
    for (j = 0; j < N; ++j) {
      printf("%s%+12.6f", (j == 0) ? "[" : "\t", A[i][j]);
    }
    printf("]\n");
  }
} /*}}}*/

void plu(double **P, double **L, double **U) { /*{{{*/
  int i = 0;
  int j = 0;
  int k = 0;
  int p = 0;
  double m = 0.0;

  for (k = 0; k < N - 1; ++k) {
    m = U[k][k];
    p = k;
    for (i = k; i < N; ++i) {
      if (ABS(U[i][k]) > ABS(m)) {
        m = U[i][k];
        p = i;
      }
    }
    if (p != k) {
      for (j = 0; j < N; ++j) {
        m = U[k][j];
        U[k][j] = U[p][j];
        U[p][j] = m;
        m = P[k][j];
        P[k][j] = P[p][j];
        P[p][j] = m;
      }
    }
    for (i = k + 1; i < N; ++i) {
      L[i][k] = U[i][k] / U[k][k];
      for (j = k; j < N; ++j) {
        U[i][j] -= L[i][k] * U[k][j];
      }
    }
  }
} /*}}}*/

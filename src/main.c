#include <stdio.h>
#include <stdlib.h>

#define ABS(X) (X >= 0 ? X : -X)
#define DIM 4

void allocate(double ***, int);
void setfree(double ***, int);
void display(double **, int, const char *const);
void init(double **, int, double ***, double ***, double ***);
double plu(int, double ***, double ***, double ***);
void transpose(double ***, int);
void reduce(double **, int, double ***, int, int);
void inverse(double **, int, double, double ***);
void product(double **, double **, double ***, int);

int main(void) {
  double **A = NULL;
  double **P = NULL;
  double **L = NULL;
  double **U = NULL;
  double det = 1.0;
  double **C = NULL;

  allocate(&A, DIM);
  allocate(&P, DIM);
  allocate(&L, DIM);
  allocate(&U, DIM);
  allocate(&C, DIM);

  A[0][0] = 10.0;
  A[0][1] = 21.0;
  A[0][2] = -3.0;
  A[0][3] = -4.0;
  A[1][0] = -5.0;
  A[1][1] = -6.0;
  A[1][2] = -7.0;
  A[1][3] = -8.0;
  A[2][0] = -9.0;
  A[2][1] = 10.0;
  A[2][2] = 11.0;
  A[2][3] = 12.0;
  A[3][0] = 13.0;
  A[3][1] = 14.0;
  A[3][2] = 15.0;
  A[3][3] = 16.0;

  init(A, DIM, &P, &L, &U);

  det = plu(DIM, &P, &L, &U);

  display(A, DIM, "A");
  display(P, DIM, "P");
  display(L, DIM, "L");
  display(U, DIM, "U");

  if (ABS(det) > 10e-7) {
    double **Ainv = NULL;

    allocate(&Ainv, DIM);
    inverse(A, DIM, det, &Ainv);
    display(Ainv, DIM, "Ainv");
    product(A, Ainv, &C, DIM);
    display(C, DIM, "A * Ainv");
    setfree(&Ainv, DIM);
  } else {
    printf("\nDeterminant is too close to zero.\n");
  }

  setfree(&A, DIM);
  setfree(&P, DIM);
  setfree(&L, DIM);
  setfree(&U, DIM);
  setfree(&C, DIM);

  exit(EXIT_SUCCESS);
}

void
allocate(double ***A, int n) {
  int i;

  *A = malloc(n * sizeof(n * sizeof(double)));

  for (i = 0; i < n; ++i) {
    (*A)[i] = malloc(n * sizeof(double));
  }
}

void
setfree(double ***A, int n) {
  int i;

  for (i = 0; i < n; ++i) {
    free((*A)[i]);
  }

  free(*A);
}

void
display(double **const A, int n, const char *const label) {
  int i;
  int j;

  printf("\n%s:\n", label);

  for (i = 0; i < n; ++i) {
    printf("[");
    for (j = 0; j < n; ++j) {
      printf("%+12.6f", A[i][j]);
    }
    printf("]\n");
  }
}

void
init(double **A, int n, double ***P, double ***L, double ***U) {
  int i;
  int j;

  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      (*P)[i][j] = (i == j) ? 1.0 : 0.0;
      (*L)[i][j] = (i == j) ? 1.0 : 0.0;
      (*U)[i][j] = A[i][j];
    }
  }
}

double
plu(int n, double ***P, double ***L, double ***U) {
  int i = 0;
  int j = 0;
  int k = 0;
  int p = 0;
  double m = 0.0;
  double det = 1.0;

  for (k = 0; k < n - 1; ++k) {
    m = (*U)[k][k];
    p = k;
    for (i = k; i < n; ++i) {
      if (ABS((*U)[i][k]) > ABS(m)) {
        m = (*U)[i][k];
        p = i;
      }
    }
    if (p != k) {
      for (j = 0; j < n; ++j) {
        m = (*U)[k][j];
        (*U)[k][j] = (*U)[p][j];
        (*U)[p][j] = m;
        m = (*P)[k][j];
        (*P)[k][j] = (*P)[p][j];
        (*P)[p][j] = m;
      }
      det *= -1.0;
    }
    det *= (*U)[k][k];
    for (i = k + 1; i < n; ++i) {
      (*L)[i][k] = (*U)[i][k] / (*U)[k][k];
      for (j = k; j < n; ++j) {
        (*U)[i][j] -= (*L)[i][k] * (*U)[k][j];
      }
    }
  }
  return det * (*U)[n - 1][n - 1];
}

void
transpose(double ***A, int n) {
  int i;
  int j;
  double m;

  for (i = 0; i < n - 1; ++i) {
    for (j = i + 1; j < n; ++j) {
      if (i != j) {
        m = (*A)[i][j];
        (*A)[i][j] = (*A)[j][i];
        (*A)[j][i] = m;
      }
    }
  }
}

void
reduce(double **A, int n, double ***a, int i, int j) {
  int k;
  int l;
  int r;
  int s;

  for (k = 0; k < n; ++k) {
    if (k != i) {
      r = (k < i) ? k : k - 1;
      for (l = 0; l < n; ++l) {
        if (l != j) {
          s = (l < j) ? l : l - 1;
          (*a)[r][s] = A[k][l];
        }
      }
    }
  }
}

void
inverse(double **A, int n, double detA, double ***Ainv) {
  double **a = NULL;
  double **p = NULL;
  double **l = NULL;
  double **u = NULL;
  int i;
  int j;

  allocate(&a, n - 1);
  allocate(&p, n - 1);
  allocate(&l, n - 1);
  allocate(&u, n - 1);

  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      reduce(A, n, &a, i, j);
      init(a, n - 1, &p, &l, &u);
      (*Ainv)[i][j] = ((i + j) % 2 == 0 ? 1.0 : -1.0) * plu(n - 1, &p, &l, &u) / detA;
    }
  }

  transpose(Ainv, n);

  setfree(&a, n - 1);
  setfree(&p, n - 1);
  setfree(&l, n - 1);
  setfree(&u, n - 1);
}

void
product(double **A, double **B, double ***C, int n) {
  int i;
  int j;
  int k;

  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      (*C)[i][j] = 0.0;
      for (k = 0; k < n; ++k) {
        (*C)[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

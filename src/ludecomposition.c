#include "matrix.h"

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

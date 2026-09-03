#include <stdio.h>
#include <stdlib.h>

#define MAX(X, Y) (((X) >= (Y)) ? (X) : (Y))
#define ABS(X) (MAX(-1.0 * (X), (X)))

int power(int b, int n);
double vec2dec(int b, int* X, int n);
void dec2vec(double x, int b, int* X, int n);

int main(void)
{
  double x = 0.212;
  int b = 3;
  int* X = NULL;
  int n = 6;
  int i;

  X = malloc((n + 1) * sizeof(int));

  X[0] = 0;

  dec2vec(x, b, X, n);

  printf("x = %f\nb = %d\nn = %d\n0.", x, b, n);

  for (i = 1; i <= n; i++) {
    printf("%d", X[i]);
  }

  printf("\n%f\n", vec2dec(b, X, n));

  free(X);

  exit(EXIT_SUCCESS);
}

int power(int b, int n)
{
  int p = 1;

  while (n > 0) {
    p *= b;
    --n;
  }

  return p;
}

double vec2dec(int b, int* X, int n)
{
  double x = 0.0;
  int i;

  for (i = 1; i <= n; i++) {
    x += (double)X[i] / (double)power(b, i);
  }

  return x;
}

void dec2vec(double x, int b, int* X, int n)
{
  double s;
  int i;

  X[1] = (int)(b * x);
  s = (double)X[1] / (double)power(b, 1);

  for (i = 2; i <= n; i++) {
    X[i] = (int)((x - s) * power(b, i));
    s += (double)X[i] / (double)power(b, i);
  }
}

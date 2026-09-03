#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int factorial(int n);
int binomial(int n, int k);
void allocate(int**** powerset, int n);
void deallocate(int**** powerset, int n);
void initialize(int**** powerset, int n);
void prettyprint(int**** powerset, int n);

int main(int argc, char** argv) {
  if (argc == 3 && !strcmp(argv[1], "-n")) {
    int*** powerset = NULL;
    int n = atoi(argv[2]);

    allocate(&powerset, n);
    initialize(&powerset, n);
    prettyprint(&powerset, n);
    deallocate(&powerset, n);

    exit(EXIT_SUCCESS);
  } else {
    printf("wrong usage.\n");
    exit(EXIT_FAILURE);
  }
}

int factorial(int n)
{
  int f = 1;

  while (n > 1) {
    f *= n--;
  }

  return f;
}

int binomial(int n, int k)
{
  return (n >= k) ? factorial(n) / (factorial(k) * factorial(n - k)) : 0;
}

void allocate(int**** powerset, int n)
{
  int i;
  int j;
  int b;

  (*powerset) = malloc((n + 1) * sizeof(int***));

  for (i = 0; i <= n; ++i) {
    b = binomial(n, i);
    (*powerset)[i] = malloc(b * sizeof(int**));
    for (j = 0; j < b; ++j) {
      (*powerset)[i][j] = malloc(((i > 0) ? i : 1) * sizeof(int*));
    }
  }
}

void deallocate(int**** powerset, int n)
{
  int i;
  int j;
  int b;

  for (i = 0; i <= n; ++i) {
    b = binomial(n, i);
    for (j = 0; j < b; ++j) {
      free((*powerset)[i][j]);
    }
    free((*powerset)[i]);
  }

  free(*powerset);
}

void initialize(int**** powerset, int n)
{
  int i;
  int j;
  int k;
  int l;
  int m;
  int b;

  (*powerset)[0][0][0] = '*';

  for (i = 0; i < n; ++i) {
    (*powerset)[1][i][0] = i;
    (*powerset)[n][0][i] = i;
  }

  for (i = 2; i <= n - 1; ++i) {
    b = binomial(n, i - 1);
    for (j = 0, k = 0; j <= b - 1; ++j) {
      if ((*powerset)[i - 1][j][i - 2] <= n - 2) {
        for (l = (*powerset)[i - 1][j][i - 2] + 1; l <= n - 1; ++k, ++l) {
          for (m = 0; m <= i - 1; ++m) {
            (*powerset)[i][k][m] = (m <= i - 2) ? (*powerset)[i - 1][j][m] : l;
          }
        }
      }
    }
  }
}

void prettyprint(int**** powerset, int n)
{
  int i;
  int j;
  int k;
  int b;

  for (i = 0; i <= n; ++i) {
    printf("%d: ", i);
    b = binomial(n, i);
    for (j = 0; j < b; ++j) {
      printf(" {");
      for (k = 0; k < i; ++k) {
        printf(" %d ", (*powerset)[i][j][k]);
      }
      printf("} ");
    }
    printf("\n");
  }
}

#include <stdio.h>

long long factorial(int n) {
  long long f = 1;
  for (int i = 2; i <= n; i++) {
    f *= i;
  }
  return f;
}

int main(void) {
  int n;
  printf("Enter n (>=0): ");
  if (scanf("%d", &n) != 1) {
    printf("Error: Please enter a valid integer.\n");
    return 1;
  }
  if (n < 0) {
    printf("Error: n cannot be negative.\n");
    return 1;
  }
  if (n > 20) {
    printf("Warning: %d! may not fit in a 64-bit long long (overflow risk).\n",
           n);
  }
  long long res = factorial(n);
  printf("%d! = %lld\n", n, res);
  return 0;
}

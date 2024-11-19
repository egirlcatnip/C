#include <stdio.h>
int is_prime_iter(int n, int divisor) {
  if (n <= 1) {
    return 0;
  }

  // Optimazitazion O(n) -> O(sqrt(n))
  if ((divisor * divisor) > n) {
    return 1;
  }

  if (divisor == n) {
    return 1;
  }

  if (n % divisor == 0) {
    return 0;
  }

  return is_prime_iter(n, divisor + 1);
}

int is_prime(int n) { return is_prime_iter(n, 2); }

void prime(int n) {

  int result = is_prime(n);

  if (result) {
    printf("Number %i is prime\n", n);
  } else {
    printf("Number %i is prime\n", n);
  }
}

int closest_prime_up(int i, int ir) {
  int current = i + ir;

  if (is_prime(current)) {
    printf("Found prime: %i\n", current);
    return current;
  } else {
    printf("loop %i\n", ir);
    return closest_prime_up(i, ir + 1);
  }
}

void difference(int i) {
  int prime = closest_prime_up(i, 1);

  if (prime) {
    printf("Difference is: %i\n", prime - i);
  }
}

int main() {
  difference(9);
  return 0;
}

/*
Starting at: 9
prime found: 11
Difference: 2
*/
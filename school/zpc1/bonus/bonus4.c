#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

// Helper functions
int str_len(char str[]) {
  int i = 0;
  while (str[i] != '\0') {
    i++;
  }
  return i;
}

void split_to_two(char src[], char a[], char b[], int n) {
  int i = 0;
  while (i < n) {
    a[i] = src[i];
    i++;
  }
  a[i] = '\0';

  int j = 0;
  while (src[i] != '\0') {
    b[j] = src[i];
    i++;
    j++;
  }
  b[j] = '\0';
}

void str_to_digits(char str[], int digits[], int n) {
  //
}

void digits_to_str(int digits[], char str[], int n) {
  //
}

int digits_to_int(int digits[], int n) {
  //
}

int add(char a[], char b[], char result[], int n) {
  int a_int[n];
  int b_int[n];

  str_to_digits(a, a_int, n);
  str_to_digits(b, b_int, n);

  int added[n];
  // do addition

  char added_str[n];
  digits_to_str(added, added_str, n);

  int added_len = str_len(added_str);

  int int_max = 2147483647;
  if (added_len < int_max) {
    int number = digits_to_int(added, n);
    return number;
  }

  return 0;
};

// Implementation
int compute_sum(char src[], char result[], int n) {
  char a[n];
  char b[n];

  split_to_two(src, a, b, n);

  return add(a, b, result, 3);
};

int main(void) {
  char src[] = "123 456";
  char src_len = str_len(src);

  char result[100000];

  int num = compute_sum(src, result, src_len);

  if (num == 0) {
    // Print number from array
    for (int i = 0; i < src_len; i++) {
      printf("%d", result[i]);
    }
  }
  else {
    // Print number from int
    printf("%d", num);
  }

  return 0;
}

// Konya

// Expected output
/*

*/

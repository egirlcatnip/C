#include <stdio.h>

void print_array(int a[], int a_len) {
  printf("[");
  for (int i = 0; i < a_len; i++) {
    printf("%i", a[i]);
    if (i < a_len - 1) {
      printf(", ");
    }
  }
  printf("]");
  printf("\n");
}

void _merge(int a[], int p, int q, int r) {
  int n1 = q - p + 1;
  int n2 = r - q;

  int left[n1 + 1];
  int right[n2 + 1];
  int i;
  int j;

  for (i = 0; i < n1; i++) {
    left[i] = a[p + i];
  }
  for (j = 0; j < n2; j++) {
    right[j] = a[q + 1 + j];
  }

  left[n1] = 10000000;
  right[n2] = 10000000;

  i = 0;
  j = 0;

  for (int k = p; k <= r; k++) {
    if (left[i] <= right[j]) {
      a[k] = left[i];
      i = i + 1;
    }
    else {
      a[k] = right[j];
      j = j + 1;
    }
  }
};

int main(void) {
  int a[] = {0, 5, 4, 3, 2, 1, 0, 6, 0};
  int a_len = sizeof(a) / sizeof(a[0]);

  printf("Unsorted array:\n");
  print_array(a, a_len);
  printf("\n");

  insertion_sort(a, a_len);

  printf("Sorted array:\n");
  print_array(a, a_len);
  printf("\n");
}
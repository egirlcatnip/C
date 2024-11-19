#include <stdio.h>

void insertion_sort(int a[], int a_len) {
  for (int j = 1; j < a_len; j++) {
    int t = a[j];
    int i = j - 1;

    while (i >= 0 && a[i] > t) {
      a[i + 1] = a[i];
      i--;
    }
    a[i + 1] = t;
  }
}

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
#include <stdio.h>

void average_value() {
  double n[] = {1.5, 2};
  int len = sizeof(n) / sizeof(n[0]);

  double average = 0;

  for (int i = 0; i <= len; i++) {
    average += n[i];
  }

  average /= len;

  printf("Average: %f\n", average);
}

void find_index(int search) {
  printf("Searching for '%i'\n", search);

  int n[] = {1, 2, 3, 10, 22, 10};
  int len = sizeof(n) / sizeof(n[0]);
  int found_count = 0;

  for (int i = 0; i < len; i++) {
    if (search == n[i]) {
      printf("Found on index: [%i]\n", i);
      found_count++;
    }
  }

  if (!found_count) {
    printf("Not found\n");
  }
};

void compare_array() {
  int array1[] = {1, 2, 3};
  int array2[] = {1, 2, 4};

  int len1 = sizeof(array1) / sizeof(array1[0]);
  int len2 = sizeof(array2) / sizeof(array2[0]);

  if (len1 != len2) {
    printf("Not matching");
    return;
  }

  for (int i = 0; i < len1; i++) {
    if (array1[i] != array2[i]) {
      printf("Not matching");
      return;
    }
  };

  printf("Matching");
};

int is_non_decreasing(int a[], int a_len) {
  for (int i = 0; i < a_len; i++) {
    // printf("%i", a[i]);
    if (a[i] > a[i + 1]) {
      return 1;
    }
  }
  return 0;
}

int main() {
  // find_index(10);

  return 0;
}

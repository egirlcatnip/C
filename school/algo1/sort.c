#include <stdio.h>
#include <string.h>

void no_sort(int a[], int a_len) {
  /*
  no_sort(array, length):
    return
  */
  return;
}

void selection_sort(int a[], int a_len) {
  /*
  selection_sort(array, length):
    for j <- 0 to (length - 2) {
      min <- j
      for i <- (j + 1) to (length - 1) {
        if array[i] < array[min] then
          min <- i
      }
      swap array[j] and array[min]
    }
  */

  for (int j = 0; j <= a_len - 2; j++) {
    int min = j;
    for (int i = j + 1; i < a_len; i++) {
      if (a[i] < a[min]) {
        min = i;
      }
    }

    int tmp = a[j];
    a[j] = a[min];
    a[min] = tmp;
  }
}

void insertion_sort(int a[], int a_len) {
  /*
  insertion_sort(array, length):
    for j <- 1 to length {
      t <- array[j]
      i <- j - 1
      while i >= 0 and array[i] > t {
        array[i + 1] <- array[i]
        i <- i - 1
      }
      array[i + 1] <- t
    }
  */

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

void bubble_sort(int a[], int a_len) {
  /*
  bubble_sort(array, length):
    for i <- 0 to (length - 1) {
      for j <- 0 to (length - 1 - i) {
        if array[j] > array[j + 1] then
          swap array[j] and array[j + 1]
      }
    }
  */

  for (int i = 0; i < a_len - 1; i++) {
    for (int j = 0; j < a_len - 1 - i; j++) {
      if (a[j] > a[j + 1]) {
        int tmp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = tmp;
      }
    }
  }
}

void _merge(int a[], int p, int q, int r) {
  /*
  _merge(array, p, q, r):
    n1 <- q - p + 1
    n2 <- r - q
    left <- new array of size n1
    right <- new array of size n2
    for i <- 0 to (n1 - 1) {
      left[i] <- array[p + i]
    }
    for j <- 0 to (n2 - 1) {
      right[j] <- array[q + 1 + j]
    }
    left[n1] <- sentinel value
    right[n2] <- sentinel value
    i <- 0
    j <- 0
    for k <- p to (r - 1) {
      if left[i] <= right[j] then
        array[k] <- left[i]
        i <- i + 1
      else
        array[k] <- right[j]
        j <- j + 1
    }
  */

  int n1 = q - p + 1;
  int n2 = r - q;

  int left[n1];
  int right[n2];
  int i;
  int j;

  for (i = 0; i < n1 - 1; i++) {
    left[i] = a[p + i];
  };
  for (j = 0; j < n2 - 1; j++) {
    right[j] = a[q + 1 + j];
  };

  left[n1] = 10000000;
  right[n2] = 10000000;

  i = 0;
  j = 0;

  for (int k = p; k < r; k++) {
    if (left[i] <= right[j]) {
      a[k] = left[i];
      i = i + 1;
    } else {
      a[k] = right[j];
      j = j + 1;
    }
  }
};

void merge_sort(int a[], int p, int r) {
  /*
  merge_sort(array, p, r):
    if p < r then
      q <- (p + r) / 2
      merge_sort(array, p, q)
      merge_sort(array, q + 1, r)
      _merge(array, p, q, r)
  */

  if (p < r) {
    int q = (p + r) / 2;
    merge_sort(a, p, q);
    merge_sort(a, q + 1, r);

    _merge(a, p, q, r);
  }
}

void _swap(int a[], int i, int j) {
  /*
  _swap(array, i, j):
    tmp <- array[i]
    array[i] <- array[j]
    array[j] <- tmp
  */

  int tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}

int _quick_sort_partition(int a[], int p, int r) {
  /*
  _quick_sort_partition(array, p, r):
    pivot <- array[r]
    i <- p - 1
    for j <- p to (r - 1) {
      if array[j] <= pivot then
        i <- i + 1
        _swap(array, i, j)
    }
    _swap(array, i + 1, r)
    return i + 1
  */

  int pivot = a[r];
  int i = p - 1;

  for (int j = p; j < r; j++) {
    if (a[j] <= pivot) {
      i++;
      _swap(a, i, j);
    }
  }

  _swap(a, i + 1, r); // Place pivot at its correct position
  return i + 1;
}

void quick_sort(int a[], int p, int r) {
  /*
  quick_sort(array, p, r):
    if p < r then
      q <- _quick_sort_partition(array, p, r)
      quick_sort(array, p, q - 1)
      quick_sort(array, q + 1, r)
  */

  if (p < r) {
    int q = _quick_sort_partition(a, p, r);
    quick_sort(a, p, q - 1);
    quick_sort(a, q + 1, r);
  }
}

// Helper functions
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

int is_non_decreasing(int a[], int a_len) {
  int not_sorted = 0;
  for (int i = 0; i < a_len - 1; i++) {
    if (a[i] > a[i + 1]) {
      not_sorted = 1;
    }
  }
  return !not_sorted;
}

int test_sort(void (*sort_func)(int[], int), int array[], int array_len,
              const char *sort_name) {
  int array_copy[array_len];

  memcpy(array_copy, array, sizeof(int) * array_len);

  sort_func(array_copy, array_len);
  if (is_non_decreasing(array_copy, array_len)) {
    printf("%s  \tsuccess.\n", sort_name);
    print_array(array_copy, array_len);
    return 0;
  } else {
    printf("%s  \tfailed.\n", sort_name);
    print_array(array_copy, array_len);
    return 1;
  }
}

int test_quicksort(int array[], int array_len, const char *sort_name) {
  int array_copy[array_len];

  memcpy(array_copy, array, sizeof(int) * array_len);

  merge_sort(array_copy, 0, array_len - 1);

  if (is_non_decreasing(array_copy, array_len)) {
    printf("%s  \tsuccess.\n", sort_name);
    print_array(array_copy, array_len);
    return 0;
  } else {
    printf("%s  \tfailed.\n", sort_name);
    print_array(array_copy, array_len);
    return 1;
  }
}
int test_mergesort(int array[], int array_len, const char *sort_name) {
  int array_copy[array_len];

  memcpy(array_copy, array, sizeof(int) * array_len);

  quick_sort(array_copy, 0, array_len - 1);

  if (is_non_decreasing(array_copy, array_len)) {
    printf("%s  \tsuccess.\n", sort_name);
    print_array(array_copy, array_len);
    return 0;
  } else {
    printf("%s  \tfailed.\n", sort_name);
    print_array(array_copy, array_len);
    return 1;
  }
}

int main() {
#define INIT_VALUES {0, 5, 4, 3, 2, 1, 0, 6, 0}

  int array[] = INIT_VALUES;

  int len = sizeof(array) / sizeof(array[0]);

  printf("Unsorted array:\n");
  print_array(array, len);
  printf("\n");

  // test_sort(no_sort, array, len, "None   ");

  // test_sort(selection_sort, array, len, "Selection");
  // test_sort(insertion_sort, array, len, "Insertion");
  // test_sort(bubble_sort, array, len, "Bubble");
  // test_quicksort(array, len, "Quick Sort");
  test_mergesort(array, len, "Merge Sort");

  return 0;
}
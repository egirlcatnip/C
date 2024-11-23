#include <bits/posix2_lim.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

////////////////////////////////
// Function Prototypes        //
////////////////////////////////

long int insertion_sort_with_counting(int pole[], int velikost, int poradi);

long int merge_sort_with_counting(int pole[], int velikost, int poradi);

long int merge_insertion_sort_with_counting(int pole[], int velikost, int poradi, int mezni_velikost);

////////////////////////////////
// Function Implementations   //
////////////////////////////////

////////////////////////////////
// Insertion sort             //
////////////////////////////////
long int insertion_sort_with_counting(int pole[], int velikost, int poradi) {
  long int comparison_count = 0;

  for (int j = 1; j < velikost; j++) {
    int t = pole[j];
    int i = j - 1;

    while (i >= 0 && pole[i] > t) {
      pole[i + 1] = pole[i];
      comparison_count++;
      i--;
    }
    pole[i + 1] = t;
  }

  return comparison_count;
};

////////////////////////////////
// Merge sort                 //
////////////////////////////////
int _merge(int a[], int p, int q, int r) {
  int comparison_count = 0;

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
      comparison_count++;

      a[k] = left[i];
      i = i + 1;
    }
    else {
      a[k] = right[j];
      j = j + 1;
    }
  }
  return comparison_count;
};

long int _merge_sort(int array[], int p, int r, int comparison_count) {
  if (p < r) {
    int q = (p + r) / 2;

    comparison_count = _merge_sort(array, p, q, comparison_count);
    comparison_count = _merge_sort(array, q + 1, r, comparison_count);

    comparison_count += _merge(array, p, q, r);
  }

  return comparison_count;
}

long int merge_sort_with_counting(int pole[], int velikost, int poradi) {
  long int comparison_count = 0;

  comparison_count = _merge_sort(pole, 0, velikost - 1, 0);

  return comparison_count;
};

////////////////////////////////
// Merge-insertion sort       //
////////////////////////////////
long int merge_insertion_sort_with_counting(int pole[], int velikost, int poradi, int mezni_velikost) {
  long int comparison_count = 0;

  if (velikost > mezni_velikost) {
    // Sort with merge sort
    comparison_count = merge_sort_with_counting(pole, velikost, poradi);
  }
  else {
    // Sort with insertion sort
    comparison_count = insertion_sort_with_counting(pole, velikost, poradi);
  }

  return comparison_count;
};

////////////////////////////////
// Helper functions           //
////////////////////////////////

// Print array
void print_array_up_to(int a[], int len, int up_to) {
  if (up_to > len) {
    up_to = len;
  }

  printf("[");
  for (int i = 0; i < len && i < up_to; i++) {
    printf("%i", a[i]);
    if (i < up_to - 1) {
      printf(", ");
    }
  }
  if (up_to < len) {
    printf("...");
  }

  printf("]");
  printf("\n");
}

void print_array(int array[], int len) {
  print_array_up_to(array, len, len);
}

// Compare arrays
void compare_arrays(int array1[], int array2[], int array3[], int len, int up_to) {
  bool are_equal = true;

  for (int i = 0; i < len; i++) {
    if (array1[i] != array2[i] || array1[i] != array3[i]) {
      are_equal = false;
      break;
    }
  }

  if (are_equal) {
    printf("Arrays are equal\n");
    /*
    // No need to print the arrays if they are equal
    printf("\n");

    printf("Insertion sort:\n");
    print_array_up_to(array1, len, up_to);

    printf("Merge sort:\n");
    print_array_up_to(array2, len, up_to);

    printf("Insert-merge sort:\n");
    print_array_up_to(array3, len, up_to);
    */

    return;
  }
  else {
    printf("Arrays are not equal\n");
    printf("\n");

    printf("Insertion sort:\n");
    print_array_up_to(array1, len, up_to);

    printf("Merge sort:\n");
    print_array_up_to(array2, len, up_to);

    printf("Insert-merge sort:\n");
    print_array_up_to(array3, len, up_to);
  }
}

// Generate random numbers
void generate_random_numbers(int pole[], int velikost, int min_inclusive, int max_inclusive) {
  max_inclusive += 1;
  for (int i = 0; i < velikost; i++) {
    pole[i] = rand() % (max_inclusive - min_inclusive) + min_inclusive;
  }
}

// New random array
int *new_random_array(int velikost, int min_inclusive, int max_inclusive) {
  int *pole = (int *)malloc(velikost * sizeof(int));

  // Exit on error
  if (pole == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }
  generate_random_numbers(pole, velikost, min_inclusive, max_inclusive);
  return pole;
}

int main() {
  // Array parameters
  int len = 100000;   // array_length
  int sort_order = 0; // 0 for ascending (>), 1 for descending (<)
  int max = 1000;     // maximum value of elements in arrays
  int min = 0;        // minimum value of elements in arrays
  int up_to = 5;      // print up to this many elements
  // up_to = len;     // set to len for printing all elements

  int mezni_velikost = 1000; // threshold number for merge_insertion_sort

  int array[len];

  // New seed for random numbers
  srand(time(NULL));

  // Initialize all arrays to the same random values by copying the random array
  int *random_array = new_random_array(len, min, max);
  printf("Random array:\n");
  print_array_up_to(random_array, len, up_to);
  printf("\n");

  int *insertion_sort_array = memcpy(malloc(len * sizeof(int)), random_array, len * sizeof(int));
  // printf("Insertion sort:\n");
  // print_array_up_to(insertion_sort_array, len, up_to);

  int *merge_sort_array = memcpy(malloc(len * sizeof(int)), random_array, len * sizeof(int));
  // printf("Merge sort:\n");
  // print_array_up_to(merge_sort_array, len, up_to);

  int *combined_sort_array = memcpy(malloc(len * sizeof(int)), random_array, len * sizeof(int));
  // printf("Insert-merge sort:\n");
  // print_array_up_to(combined_sort_array, len, up_to);

  // Sort the arrays
  long int insertion_count = insertion_sort_with_counting(insertion_sort_array, len, sort_order);
  long int merge_count = merge_sort_with_counting(merge_sort_array, len, sort_order);
  long int combined_count = merge_insertion_sort_with_counting(combined_sort_array, len, sort_order, mezni_velikost);

  // Compare the arrays
  printf("\n");
  printf("Comparing arrays:\n");
  compare_arrays(insertion_sort_array, merge_sort_array, combined_sort_array, len, up_to);

  // Print comparison operator counts
  printf("\n");
  printf("Insertion sort count of comparisons: \t %li  \n", insertion_count);
  printf("Merge sort count of comparisons: \t %li  \n", merge_count);
  printf("Combined sort count of comparisons: \t %li  \n", combined_count);

  // Clean up memory
  free(insertion_sort_array);
  free(merge_sort_array);
  free(combined_sort_array);

  return 0;
}
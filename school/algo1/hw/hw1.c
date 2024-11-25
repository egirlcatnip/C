#include <stdbool.h> // true & false
#include <stdio.h>   // printf
#include <stdlib.h>  // rand, srand
#include <time.h>    // seed generation

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
// Insertion sort O(n^2)      //
////////////////////////////////
long int insertion_sort_with_counting(int pole[], int velikost, int poradi) {
  long int comparison_count = 0;
  bool ascending = poradi > 0;

  if (ascending) {
    for (int j = 1; j < velikost; j++) {
      int t = pole[j];
      int i = j - 1;

      while (i >= 0 && pole[i] > t) {
        pole[i + 1] = pole[i];
        comparison_count++;
        i--;
      }
      if (i >= 0) {
        comparison_count++;
      }
      pole[i + 1] = t;
    }
  }
  else {
    for (int j = 1; j < velikost; j++) {
      int t = pole[j];
      int i = j - 1;

      while (i >= 0 && pole[i] < t) {
        pole[i + 1] = pole[i];
        comparison_count++;
        i--;
      }
      if (i >= 0) {
        comparison_count++;
      }
      pole[i + 1] = t;
    }
  }
  return comparison_count;
}

// Merge sort helper functions
int _merge(int array[], int p, int q, int r, bool ascending) {
  int comparison_count = 0;

  int n1 = q - p + 1;
  int n2 = r - q;

  int left[n1];
  int right[n2];

  for (int i = 0; i < n1; i++) {
    left[i] = array[p + i];
  }
  for (int j = 0; j < n2; j++) {
    right[j] = array[q + 1 + j];
  }

  int i = 0, j = 0;

  for (int k = p; k <= r; k++) {
    if (ascending) {
      if (i < n1 && (j >= n2 || left[i] <= right[j])) {
        array[k] = left[i];
        i++;
        comparison_count++;
      }
      else {
        array[k] = right[j];
        j++;
        comparison_count++;
      }
    }
    else {
      if (i < n1 && (j >= n2 || left[i] >= right[j])) {
        array[k] = left[i];
        i++;
        comparison_count++;
      }
      else {
        array[k] = right[j];
        j++;
        comparison_count++;
      }
    }
  }
  return comparison_count;
}

long int _merge_sort(int array[], int p, int r, int comparison_count, bool ascending) {
  if (p < r) {
    int q = (p + r) / 2;

    comparison_count = _merge_sort(array, p, q, comparison_count, ascending);
    comparison_count = _merge_sort(array, q + 1, r, comparison_count, ascending);

    comparison_count += _merge(array, p, q, r, ascending);
  }

  return comparison_count;
}

////////////////////////////////
// Merge sort O(n*log(n))     //
////////////////////////////////
long int merge_sort_with_counting(int pole[], int velikost, int poradi) {
  bool ascending = poradi > 0;
  long int comparison_count = 0;

  comparison_count = _merge_sort(pole, 0, velikost - 1, 0, ascending);

  return comparison_count;
}

// Merge-insertion sort helper function
long int _hybrid_sort(int array[], int p, int r, int comparison_count, int mezni_velikost, bool ascending) {
  if (r - p + 1 <= mezni_velikost) {
    comparison_count += insertion_sort_with_counting(&array[p], r - p + 1, ascending ? 1 : 0);
  }
  else if (p < r) {
    int q = (p + r) / 2;

    comparison_count = _hybrid_sort(array, p, q, comparison_count, mezni_velikost, ascending);
    comparison_count = _hybrid_sort(array, q + 1, r, comparison_count, mezni_velikost, ascending);

    comparison_count += _merge(array, p, q, r, ascending);
  }
  return comparison_count;
}

////////////////////////////////
// Merge-insertion sort       //
////////////////////////////////
long int merge_insertion_sort_with_counting(int pole[], int velikost, int poradi, int mezni_velikost) {
  long int comparison_count = 0;
  bool ascending = poradi > 0;

  comparison_count = _hybrid_sort(pole, 0, velikost - 1, 0, mezni_velikost, ascending);

  return comparison_count;
}

////////////////////////////////
// Helper functions           //
////////////////////////////////

// Print array from 0 to up_to
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
    printf(", ..., %i", a[len - 1]);
  }

  printf("]");
  printf("\n");
}

// Copy array
void copy_array(int *source, int *destination, int size) {
  for (int i = 0; i < size; i++) {
    destination[i] = source[i];
  }
}

// Randomize array element values
void randomize_array(int pole[], int velikost, int min, int max) {
  for (int i = 0; i < velikost; i++) {
    pole[i] = rand() % (max - min + 1) + min;
  }
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
  }
  else {
    printf("Arrays are not equal\n");

    printf("Insertion sort:\n");
    print_array_up_to(array1, len, up_to);

    printf("Merge sort:\n");
    print_array_up_to(array2, len, up_to);

    printf("Merge-insertion sort:\n");
    print_array_up_to(array3, len, up_to);
  }
}

// Function to check input parameters for validity
void check_parameters(int len, int sort_order, int max, int min, int up_to, int mezni_velikost) {
  bool error = false;

  if (len <= 0) {
    printf("Error: Array length must be a positive integer.\n");
    error = true;
  }
  if (sort_order != 0 && sort_order != 1) {
    printf("Error: Sort order must be 0 (ascending) or 1 (descending).\n");
    error = true;
  }
  if (max <= 0) {
    printf("Error: Maximum value must be >= 1.\n");
    error = true;
  }
  if (min < 0) {
    printf("Error: Minimum value must be >= 0.\n");
    error = true;
  }
  if (min >= max) {
    printf("Error: Minimum value must be less than the maximum value.\n");
    error = true;
  }
  if (up_to <= 0) {
    printf("Error: Print limit must be >= 1.\n");
    error = true;
  }
  if (mezni_velikost <= 0) {
    printf("Error: Threshold size must be >= 1.\n");
    error = true;
  }

  if (error) {
    exit(1); // Exit the program if there are any errors
  }
}

// Compare speeds of algorithms by ratios, with clearer outputs
void compare_speeds(long int insertion_comp_count, long int merge_comp_count, long int hybrid_comp_count, int len) {
  float merge_insertion_ratio = 0;
  float hybrid_insertion_ratio = 0;
  float merge_hybrid_ratio = 0;
  float insertion_merge_ratio = 0;
  float hybrid_merge_ratio = 0;

  if (insertion_comp_count < merge_comp_count && insertion_comp_count < hybrid_comp_count) {
    merge_insertion_ratio = ((float)merge_comp_count / insertion_comp_count);
    hybrid_insertion_ratio = ((float)hybrid_comp_count / insertion_comp_count);
    printf("Insertion sort is the fastest.\n");
    printf("\n");
    printf("Insertion sort is roughly %.3f times faster than merge sort.\n", merge_insertion_ratio);
    printf("Insertion sort is roughly %.3f times faster than hybrid sort.\n", hybrid_insertion_ratio);
  }
  else if (merge_comp_count < insertion_comp_count && merge_comp_count < hybrid_comp_count) {
    insertion_merge_ratio = ((float)insertion_comp_count / merge_comp_count);
    hybrid_merge_ratio = ((float)hybrid_comp_count / merge_comp_count);
    printf("Merge sort is the fastest.\n");
    printf("\n");
    printf("Merge sort is roughly %.3f times faster than insertion sort.\n", insertion_merge_ratio);
    printf("Merge sort is roughly %.3f times faster than hybrid sort.\n", hybrid_merge_ratio);
  }
  else if (hybrid_comp_count < insertion_comp_count && hybrid_comp_count < merge_comp_count) {
    insertion_merge_ratio = ((float)insertion_comp_count / hybrid_comp_count);
    merge_hybrid_ratio = ((float)merge_comp_count / hybrid_comp_count);
    merge_insertion_ratio = ((float)insertion_comp_count / merge_comp_count);

    printf("Hybrid sort is the fastest.\n");
    printf("\n");
    printf("Hybrid sort is roughly %.3f times faster than insertion sort.\n", insertion_merge_ratio);
    printf("Hybrid sort is roughly %.3f times faster than merge sort.\n", merge_hybrid_ratio);
  }
}

////////////////////////////////
// Main function              //
////////////////////////////////
int main() {
  // Array parameters
  int len = 100000;   // array_length, 100_000 by default
  int sort_order = 1; // 0 for ascending (>), 1 for descending (<)

  // Random number parameters
  int max = 10000000; // maximum value of elements in arrays
  int min = 0;        // minimum value of elements in arrays

  // Print parameters
  int up_to = 10; // print up to this many elements

  int mezni_velikost = 20; // threshold number for merge_insertion_sort
  // len < mezni_velikost -> insertion_sort
  // len >= mezni_velikost -> merge_sort

  // Check the validity of the parameters
  check_parameters(len, sort_order, max, min, up_to, mezni_velikost);

  // Generate seed for random numbers based on current system time
  int seed = time(NULL);
  // seed = 10;
  // srand(seed);

  // Initialize all arrays to the same random values by copying the random array
  int array[len];
  randomize_array(array, len, min, max);

  printf("Random array[%i] (seed: %i)\n", len, seed);
  printf("Max: %i, Min: %i, Hybrid-sort treshold: %i \n", max, min, mezni_velikost);
  print_array_up_to(array, len, up_to);
  printf("\n");

  int insertion_sort_array[len];
  copy_array(array, insertion_sort_array, len);

  int merge_sort_array[len];
  copy_array(array, merge_sort_array, len);

  int hybrid_sort_array[len];
  copy_array(array, hybrid_sort_array, len);

  // Sort the arrays
  long int insertion_comp_count = insertion_sort_with_counting(insertion_sort_array, len, sort_order);
  long int merge_comp_count = merge_sort_with_counting(merge_sort_array, len, sort_order);
  long int hybrid_comp_count = merge_insertion_sort_with_counting(hybrid_sort_array, len, sort_order, mezni_velikost);

  // Compare the arrays
  printf("Comparing arrays:\n");
  compare_arrays(insertion_sort_array, merge_sort_array, hybrid_sort_array, len, up_to);

  // Print comparison operator counts
  printf("\n");
  printf("Insertion sort comparison count:    \t %li      \n", insertion_comp_count);
  printf("Merge sort comparison count:    \t %li      \n", merge_comp_count);
  printf("Merge-Insert sort comparison count:    \t %li      \n", hybrid_comp_count);

  // Compare the speed of the algorithms by %
  printf("\n");
  compare_speeds(insertion_comp_count, merge_comp_count, hybrid_comp_count, len);

  // Choice of array doesn't matter, they are all sorted
  printf("\n");
  printf("Sorted array - ");

  if (sort_order == 0) {
    printf("Descending (>)\n");
    print_array_up_to(insertion_sort_array, len, up_to);
  }
  else {
    printf("Ascending (<)\n");
    print_array_up_to(insertion_sort_array, len, up_to);
  }

  return 0;
}

// Konya

// Expected output
/*
Random array[100000] (seed: 1732406751)
Max: 10000000, Min: 0, Hybrid-sort treshold: 20
[4233113, 206316, 2298167, 4679684, 2591968, 7194581, 91574, 5942472, 8262590, 9698191, ..., 5210281]

Comparing arrays:
Arrays are equal

Insertion sort comparison count:         2503084001
Merge sort comparison count:             1668928
Merge-Insert sort comparison count:      1655228

Merge-insertion sort is the fastest.

Merge-insertion sort is roughly 1512.229 times faster than insertion sort.
Merge-insertion sort is roughly 1.008 times faster than merge sort.

Sorted array - Descending (>)
[10000000, 9999933, 9999504, 9999487, 9999454, 9999397, 9999396, 9999333, 9999250, 9998563, ..., 46]
*/

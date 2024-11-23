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
// Insertion sort             //
////////////////////////////////
long int insertion_sort_with_counting(int pole[], int velikost, int poradi) {
  long int comparison_count = 0;
  bool ascending = poradi > 0;

  for (int j = 1; j < velikost; j++) {
    int t = pole[j];
    int i = j - 1;

    if (ascending) { // Ascending order
      while (i >= 0 && pole[i] > t) {
        pole[i + 1] = pole[i];
        comparison_count++;
        i--;
      }
    }
    else { // Descending order
      while (i >= 0 && pole[i] < t) {
        pole[i + 1] = pole[i];
        comparison_count++;
        i--;
      }
    }

    pole[i + 1] = t;
  }

  return comparison_count;
}

////////////////////////////////
// Merge sort                 //
////////////////////////////////
int _merge(int array[], int p, int q, int r, bool ascending) {
  int comparison_count = 0;

  int n1 = q - p + 1;
  int n2 = r - q;

  int left[n1 + 1];
  int right[n2 + 1];

  for (int i = 0; i < n1; i++) {
    left[i] = array[p + i];
  }
  for (int j = 0; j < n2; j++) {
    right[j] = array[q + 1 + j];
  }

  int i = 0;
  int j = 0;

  for (int k = p; k <= r; k++) {
    if (ascending) {
      if (i < n1 && (j >= n2 || left[i] <= right[j])) {
        array[k] = left[i];
        i++;
      }
      else {
        array[k] = right[j];
        j++;
      }
    }
    else {
      if (i < n1 && (j >= n2 || left[i] >= right[j])) {
        array[k] = left[i];
        i++;
      }
      else {
        array[k] = right[j];
        j++;
      }
    }
    comparison_count++;
  }
  return comparison_count;
};

long int _merge_sort(int array[], int p, int r, int comparison_count, bool ascending) {
  if (p < r) {
    int q = (p + r) / 2;

    comparison_count = _merge_sort(array, p, q, comparison_count, ascending);
    comparison_count = _merge_sort(array, q + 1, r, comparison_count, ascending);

    comparison_count += _merge(array, p, q, r, ascending);
  }

  return comparison_count;
}

long int merge_sort_with_counting(int pole[], int velikost, int poradi) {
  bool ascending = poradi > 0;
  long int comparison_count = 0;

  comparison_count = _merge_sort(pole, 0, velikost - 1, 0, ascending);

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

// Copy array
void copy_array(int *source, int *destination, int size) {
  for (int i = 0; i < size; i++) {
    destination[i] = source[i];
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
int random_number(int min_inclusive, int max_inclusive) {
  max_inclusive += 1;
  int number = rand() % (max_inclusive - min_inclusive) + min_inclusive;

  return number;
}

void randomize_array(int pole[], int velikost, int min_inclusive, int max_inclusive) {
  for (int i = 0; i < velikost; i++) {
    pole[i] = random_number(min_inclusive, max_inclusive);
  }
}

// New random array

int main() {
  // Array parameters
  int len = 100000;   // array_length
  int sort_order = 0; // 0 for ascending (>), 1 for descending (<)

  // Random number parameters
  int max = 10; // maximum value of elements in arrays
  int min = 0;  // minimum value of elements in arrays

  // Print parameters
  int up_to = 10; // print up to this many elements
  // up_to = len;   // set to len for printing all elements

  int mezni_velikost = 12; // threshold number for merge_insertion_sort
  // len < mezni_velikost -> insertion_sort
  // len >= mezni_velikost -> merge_sort

  // Generate seed for random numbers based on current system time
  int seed = time(NULL);
  srand(seed);

  // Initialize all arrays to the same random values by copying the random array
  int array[len];
  randomize_array(array, len, min, max);

  printf("Random array (seed: %i):\n", seed);
  print_array_up_to(array, len, up_to);
  printf("\n");

  int insertion_sort_array[len];
  copy_array(array, insertion_sort_array, len);

  int merge_sort_array[len];
  copy_array(array, merge_sort_array, len);

  int combined_sort_array[len];
  copy_array(array, combined_sort_array, len);

  // Sort the arrays
  long int insertion_count = insertion_sort_with_counting(insertion_sort_array, len, sort_order);
  long int merge_count = merge_sort_with_counting(merge_sort_array, len, sort_order);
  long int merge_isert_count = merge_insertion_sort_with_counting(combined_sort_array, len, sort_order, mezni_velikost);

  // Compare the arrays
  printf("Comparing arrays:\n");
  compare_arrays(insertion_sort_array, merge_sort_array, combined_sort_array, len, up_to);

  // Print comparison operator counts
  printf("\n");
  printf("Insertion sort count of comparisons:\t %li  \n", insertion_count);
  printf("Merge sort count of comparisons:\t %li  \n", merge_count);
  printf("Merge-Insert sort count of comparisons:\t %li  \n", merge_isert_count);

  // Choice of array doesn't matter, they are all sorted
  // print_array_up_to(insertion_sort_array, len, up_to);

  return 0;
}

// Konya
//
// Expected output
/*
Random array (seed: 1732388521):
[4, 6, 0, 6, 1, 0, 9, 7, 8, 8...]

Comparing arrays:
Arrays are equal

Insertion sort count of comparisons:     2273017584
Merge sort count of comparisons:         1668928
Merge-Insert sort count of comparisons:  1668928
*/
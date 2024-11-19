#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

int root(int n) {
  int i = 1;
  while (i * i < n) {
    i++;
  }
  return i;
}

int get_matrix_by_index(int matrix[], int m, int index_x, int index_y) {
  assert(!(index_x > m || index_y > m || index_x < 0 || index_y < 0));

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      int value = matrix[index_x * m + index_y];
      assert(!(value != 0 && value != 1));
    }
  }

  return matrix[index_x * m + index_y];
}

void check_matrix(int matrix[], int m) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      int value = get_matrix_by_index(matrix, m, i, j);
      assert(value != -1);
    }
  }
}

void print_matrix(int matrix[], int m) {
  check_matrix(matrix, m);

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      int value = get_matrix_by_index(matrix, m, i, j);

      printf("%d  ", value);
    }
    printf("\n");
  }
}

// Bonus functions:
int equivalence(int r[], int m) {

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      int value_i = get_matrix_by_index(r, m, i, j);
      int value_j = get_matrix_by_index(r, m, j, i);

      if (value_i != value_j) {
        return false;
      }
    }
  }
  return true;
};

void transitive_closure(int r[], int m) {
  // Change stuff
};

int main(void) {
  int matrix[] = {
      0, 0, 0, 0, //
      0, 0, 0, 0, //
      0, 0, 1, 0, //
      0, 0, 0, 1, //
  };
  int m = 4;

  printf("Matrix:\n");
  print_matrix(matrix, m);

  printf("\n");

  int equivalent = equivalence(matrix, m);

  if (equivalent) {
    printf("The matrix is equivalent.\n");
  } else {
    printf("The matrix is not equivalent.\n");
  }

  printf("\n");
  printf("Transitive closure:\n");

  transitive_closure(matrix, m);

  print_matrix(matrix, m);

  return 0;
}

// Konya

// Expected output
/*
Matrix:
0  0  0  0
0  0  0  0
0  0  1  0
0  0  0  1

The matrix is equivalent.

Transitive closure:
0  0  0  0
0  0  0  0
0  0  1  0
0  0  0  1
*/

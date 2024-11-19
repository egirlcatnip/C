#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

// Helper functions
int get_matrix_by_index(int matrix[], int m, int index_x, int index_y) {
  int valid = (index_x > m || index_y > m || index_x < 0 || index_y < 0);
  assert(!valid);

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      int value = matrix[index_x * m + index_y];
      int valid = (value != 0 && value != 1);

      assert(!valid);
    }
  }
  return matrix[index_x * m + index_y];
}

void print_matrix(int matrix[], int m) {

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      int value = get_matrix_by_index(matrix, m, i, j);

      printf("%d  ", value);
    }
    printf("\n");
  }
}

// Checks
int symetric(int r[], int m) {
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

int reflexive(int r[], int m) {
  for (int i = 0; i < m; i++) {
    int value = get_matrix_by_index(r, m, i, i);

    if (value == 0) {
      return false;
    }
  }
  return true;
}

int transitive(int r[], int m) {
  return 0;
  //
};

// Exercise functions
int equivalence(int r[], int m) {
  int is_symetric = symetric(r, m);
  int is_transitive = transitive(r, m);
  int is_reflexive = reflexive(r, m);

  if (is_symetric && is_transitive && is_reflexive) {
    return true;
  } else {
    return false;
  }
};

void transitive_closure(int r[], int m) {
  // Change stuff

};

int main(void) {
  int matrix[] = {
      1, 0, 0, //
      0, 1, 0, //
      0, 0, 1, //
  };
  int m = 3;

  printf("Matrix:\n");
  print_matrix(matrix, m);

  printf("\n");

  printf("Is reflexive?: %d \n", reflexive(matrix, m));
  printf("Is symteric?: %d \n", symetric(matrix, m));
  printf("Is transitive?: %d \n", transitive(matrix, m));

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
1  0  0  0
1  1  0  0
0  0  1  0
0  0  0  1

The matrix is not equivalent.

Transitive closure:
1  1  0  0
1  1  0  0
0  0  1  0
0  0  0  1
*/

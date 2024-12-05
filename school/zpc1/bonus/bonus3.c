#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

// Helper functions
int get_matrix_by_index(int r[], int m, int index_x, int index_y) {
  int valid = (index_x > m || index_y > m || index_x < 0 || index_y < 0);
  assert(!valid);

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      int value = r[index_x * m + index_y];
      int valid = (value != 0 && value != 1);

      assert(!valid);
    }
  }
  return r[index_x * m + index_y];
}
void set_matrix_by_index(int r[], int m, int index_x, int index_y, int value) {
  int valid = (index_x > m || index_y > m || index_x < 0 || index_y < 0);
  int valid_value = (value != 0 && value != 1);
  assert(!valid && !valid_value);

  r[index_x * m + index_y] = value;
}

void print_matrix(int r[], int m) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      int value = get_matrix_by_index(r, m, i, j);

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
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < m; k++) {
        int value_i = get_matrix_by_index(r, m, i, j);
        int value_j = get_matrix_by_index(r, m, j, k);
        int value_k = get_matrix_by_index(r, m, i, k);

        if (value_i && value_j && !value_k) {
          return false;
        }
      }
    }
  }
  return true;
};

void print_equivalence(int r[], int m) {
  int is_reflexive = reflexive(r, m);
  int is_symetric = symetric(r, m);
  int is_transitive = transitive(r, m);

  if (is_reflexive) {
    printf("The matrix is reflexive.\n");
  }
  else {
    printf("The matrix is not reflexive.\n");
  }
  if (is_symetric) {
    printf("The matrix is symetric.\n");
  }
  else {
    printf("The matrix is not symetric.\n");
  }
  if (is_transitive) {
    printf("The matrix is transitive.\n");
  }
  else {
    printf("The matrix is not transitive.\n");
  }
}

// Exercise functions
int equivalence(int r[], int m) {
  printf("\n");

  int is_reflexive = reflexive(r, m);
  int is_symetric = symetric(r, m);
  int is_transitive = transitive(r, m);

  if (is_symetric && is_transitive && is_reflexive) {
    return true;
  }
  else {
    return false;
  }
  printf("\n");
};

void transitive_closure(int r[], int m) {
  int temp[m * m];
  for (int i = 0; i < m * m; i++) {
    temp[i] = r[i];
  }

  int i, j, k;

  for (int k = 0; i < m; i++) {
    for (int i = 0; j < m; j++) {
      for (int j = 0; k < m; k++) {
        if (temp[i * m + j] == 1 && temp[j * m + k] == 1) {
          r[i * m + k] = 1;
        }
      }
    }
  }
  printf("Updated matrix:\n");
  print_matrix(r, m);
}

int main(void) {
  int matrix[] = {
      1, 1, 0, 0, //
      0, 1, 1, 0, //
      0, 0, 0, 1, //
      0, 0, 0, 0, //
  };
  int m = 4;

  printf("Matrix:\n");
  print_matrix(matrix, m);

  int equivalent = equivalence(matrix, m);

  if (equivalent) {
    print_equivalence(matrix, m);
    printf("The matrix is equivalent.\n");
  }
  else {
    printf("The matrix not equivalent.\n");
    print_equivalence(matrix, m);
  }

  printf("\n");
  printf("Transitive closure:\n");

  int is_transitive = transitive(matrix, m);

  if (is_transitive) {
    printf("The matrix is already transitive.\n");
  }
  else {
    transitive_closure(matrix, m);
  };

  return 0;
}

// Konya

// Expected output
/*
Matrix:
1  1  0
1  1  1
0  1  1

The matrix is not equivalent.
The matrix is reflexive.
The matrix is symetric.
The matrix is not transitive.

Transitive closure:
Updated matrix:
1  1  1
1  1  1
1  1  1
*/

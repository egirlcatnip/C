#include <stdio.h>

void string_values(char array[], int len) {
  for (int i = 0; i < len - 1; i++) {
    //
    char character = array[i];
    printf("array[%i] =\t '%c'-(%i)\n", i, character, character);
  }
}

int main() {
  char array1[] = "Test";

  int len1 = sizeof(array1) / sizeof(array1[0]);

  string_values(array1, len1);

  return 0;
}

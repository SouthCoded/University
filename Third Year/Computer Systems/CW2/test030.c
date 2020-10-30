#include "cs0019.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
// More boundary write error checks #2.

int main() {
  int *array = (int *)malloc(3); // oops, forgot "* sizeof(int)"
  for (int i = 0; i < 3; ++i) {
    array[i] = 0;
  }
  free(array);
  cs0019_printstatistics();
}

//! MEMORY BUG???: detected wild write during free of pointer ???
//! ???

#include "cs0019.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
// Free of invalid pointer.

int main() {
  free((void *)16);
  cs0019_printstatistics();
}

//! MEMORY BUG???: invalid free of pointer ???, not in heap
//! ???

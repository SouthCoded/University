#include "cs0019.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
// Wild free.

int main() {
  int x;
  free(&x);
  cs0019_printstatistics();
}

//! MEMORY BUG???: invalid free of pointer ???, not in heap
//! ???

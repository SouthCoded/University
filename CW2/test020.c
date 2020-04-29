#include "cs0019.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
// Double free.

int main() {
  void *ptr = malloc(2001);
  free(ptr);
  free(ptr);
  cs0019_printstatistics();
}

//! MEMORY BUG???: invalid free of pointer ???
//! ???

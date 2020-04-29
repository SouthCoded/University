#include "cs0019.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
// Wild free inside heap-allocated data.

int main() {
  void *ptr = malloc(2001);
  free((char *)ptr + 128);
  cs0019_printstatistics();
}

//! MEMORY BUG???: invalid free of pointer ???, not allocated
//! ???

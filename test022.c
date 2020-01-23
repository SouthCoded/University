#include "cs0019.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
// File name and line number of wild free.

int main() {
  void *ptr = malloc(2001);
  free((char *)ptr + 128);
  cs0019_printstatistics();
}

//! MEMORY BUG: test???.c:9: invalid free of pointer ???, not allocated
//! ???

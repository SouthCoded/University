#include "cs0019.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
// An unaligned invalid realloc.

int main() {
  char *ptr = (char *)malloc(2002);
  ptr = realloc(ptr + 7, 2003);
  cs0019_printstatistics();
}

//! MEMORY BUG???: invalid ??{realloc|free}?? of pointer ???
//! ???

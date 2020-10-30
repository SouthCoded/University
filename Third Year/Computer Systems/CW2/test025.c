#include "cs0019.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
// Invalid realloc.

int main() {
  char *ptr = (char *)malloc(2000);
  ptr = realloc(&ptr[8], 2001);
  cs0019_printstatistics();
}

//! MEMORY BUG???: invalid ??{realloc|free}?? of pointer ???
//! ???

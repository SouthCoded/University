#include "cs0019.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
// Another invalid realloc.

int main() {
  char *ptr = (char *)malloc(2002);
  ptr = realloc(&ptr, 2003);
  cs0019_printstatistics();
}

//! MEMORY BUG???: invalid ??{realloc|free}?? of pointer ???
//! ???

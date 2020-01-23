#include "cs0019.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
// Another nasty calloc.

int main() {
  char *p = (char *)calloc(0x100000001UL, 0x100000002UL);
  assert(p == NULL);
  cs0019_printstatistics();
}

//! malloc count: active          0   total          0   fail          1
//! malloc size:  active          0   total          0   fail        ???

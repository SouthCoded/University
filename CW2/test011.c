#include "cs0019.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// heap_min and heap_max checking, no overlap with other regions.

static int global;

int main() {
  for (int i = 0; i != 100; ++i) {
    size_t sz = rand() % 100;
    char *p = (char *)malloc(sz);
    free(p);
  }
  struct cs0019_statistics stat;
  cs0019_getstatistics(&stat);

  union {
    char *cptr;
    int *iptr;
    struct cs0019_statistics *statptr;
    int (*mainptr)();
  } x;
  x.iptr = &global;
  assert(x.cptr + sizeof(int) < stat.heap_min || x.cptr >= stat.heap_max);
  x.statptr = &stat;
  assert(x.cptr + sizeof(int) < stat.heap_min || x.cptr >= stat.heap_max);
  x.mainptr = &main;
  assert(x.cptr + sizeof(int) < stat.heap_min || x.cptr >= stat.heap_max);
}

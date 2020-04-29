#include "cs0019.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// heap_min and heap_max checking, more allocations.

int main() {
  char *heap_min = NULL;
  char *heap_max = NULL;
  for (int i = 0; i != 100; ++i) {
    size_t sz = rand() % 100;
    char *p = (char *)malloc(sz);
    if (!heap_min || heap_min > p) {
      heap_min = p;
    }
    if (!heap_max || heap_max < p + sz) {
      heap_max = p + sz;
    }
    free(p);
  }
  struct cs0019_statistics stat;
  cs0019_getstatistics(&stat);
  assert(heap_min >= stat.heap_min);
  assert(heap_max <= stat.heap_max);
}

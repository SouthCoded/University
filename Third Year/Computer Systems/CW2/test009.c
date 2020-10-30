#include "cs0019.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
// heap_min and heap_max checking, simple case.

int main() {
  char *p = (char *)malloc(10);
  struct cs0019_statistics stat;
  cs0019_getstatistics(&stat);
  assert(p >= stat.heap_min);
  assert(p + 10 <= stat.heap_max);
}

#include "cs0019.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
// Memory leak report with no leaks.

struct node {
  struct node *next;
};
typedef struct node node;

int main() {
  node *list = NULL;
  node *n;

  // create a list
  for (int i = 0; i < 400; ++i) {
    n = (node *)malloc(sizeof(node));
    n->next = list;
    list = n;
  }

  // free everything in it
  while ((n = list)) {
    list = n->next;
    free(n);
  }

  cs0019_printleakreport();
  printf("OK\n");
}

//! OK

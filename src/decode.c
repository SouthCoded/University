#include <stdio.h>
#include "decomp0019.h"

int main(int argc, char* argv[]) {
  if (argc < 1) {
    return 0;
  }

  if (argc != 3) {
    printf("Run with ./decode 'file_to_decode' 'output_file'\n");
    return 1;
  }

  FILE* input = fopen(argv[1], "r");
  if (input == NULL) {
    perror("Bad input");
    return 1;
  }

  FILE* output = fopen(argv[2], "w");
  if (input == NULL) {
    perror("Bad output");
    return 1;
  }

  Decode(input, output);
  fclose(input);
  fclose(output);
}

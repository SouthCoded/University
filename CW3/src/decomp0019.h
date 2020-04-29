#include <stdio.h>
#include "comp0019lib.h"

#ifndef DECOMP0019_H
#define DECOMP0019_H

#ifdef __cplusplus
extern "C" {
#endif

// Reads in compressed bytes from the stream 'in_file', decodes them in to bases
// and writes them into out_file.
void Decode(FILE* in_file, FILE* out_file);

#ifdef __cplusplus
}
#endif

#endif  // Include guard

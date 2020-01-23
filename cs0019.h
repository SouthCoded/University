#ifndef CS0019_H
#define CS0019_H 1
#include <inttypes.h>
#include <stdlib.h>

/// cs0019_malloc(sz, file, line)
///    Return a pointer to `sz` bytes of newly-allocated dynamic memory.
void *cs0019_malloc(size_t sz, const char *file, int line);

/// cs0019_free(ptr, file, line)
///    Free the memory space pointed to by `ptr`.
void cs0019_free(void *ptr, const char *file, int line);

/// cs0019_realloc(ptr, sz, file, line)
///    Reallocate the dynamic memory pointed to by `ptr` to hold at least
///    `sz` bytes, returning a pointer to the new block.
void *cs0019_realloc(void *ptr, size_t sz, const char *file, int line);

/// cs0019_calloc(nmemb, sz, file, line)
///    Return a pointer to newly-allocated dynamic memory big enough to
///    hold an array of `nmemb` elements of `sz` bytes each. The memory
///    is initialized to zero.
void *cs0019_calloc(size_t nmemb, size_t sz, const char *file, int line);

/// cs0019_statistics
///    Structure tracking memory statistics.
struct cs0019_statistics {
  unsigned long long nactive;     // # active allocations
  unsigned long long active_size; // # bytes in active allocations
  unsigned long long ntotal;      // # total allocations
  unsigned long long total_size;  // # bytes in total allocations
  unsigned long long nfail;       // # failed allocation attempts
  unsigned long long fail_size;   // # bytes in failed alloc attempts
  char *heap_min;                 // smallest allocated addr
  char *heap_max;                 // largest allocated addr
};

/// cs0019_getstatistics(stats)
///    Store the current memory statistics in `*stats`.
void cs0019_getstatistics(struct cs0019_statistics *stats);

/// cs0019_printstatistics()
///    Print the current memory statistics.
void cs0019_printstatistics(void);

/// cs0019_printleakreport()
///    Print a report of all currently-active allocated blocks of dynamic
///    memory.
void cs0019_printleakreport(void);

/// cs0019_getstatistics(stats)
///    Store the current memory statistics in `*stats`.
void cs0019_getstatistics(struct cs0019_statistics *stats);

/// cs0019_printheavyhitterreport()
///    Print a report of all the heavy hitters as described
///    in the coursework handout.
void cs0019_printheavyhitterreport(void);

#if !CS0019_DISABLE
// Redefine the `malloc` family of calls to use our versions.
#define malloc(sz) cs0019_malloc((sz), __FILE__, __LINE__)
#define free(ptr) cs0019_free((ptr), __FILE__, __LINE__)
#define realloc(ptr, sz) cs0019_realloc((ptr), (sz), __FILE__, __LINE__)
#define calloc(nmemb, sz) cs0019_calloc((nmemb), (sz), __FILE__, __LINE__)
#endif

// `cs0019.c` should use these functions rather than malloc() and free().
void *base_malloc(size_t sz);
void base_free(void *ptr);
void base_malloc_disable(int is_disabled);

#endif

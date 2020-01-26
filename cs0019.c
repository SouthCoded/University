#define CS0019_DISABLE 1
#include "cs0019.h"
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define metadata_size sizeof(size_t) //8 bytes

int total_malloc = 0;
int total_size = 0;
int activeAlloc = 0;
int activeAlloc_size = 0;
int failed = 0;
int failed_size = 0;
char* heap_min = (char*) 0xfffffffffffff;
char* heap_max = (char*) 0x0000000000000;
struct node* head = NULL; 

struct metadata 
{ 
   size_t size; 
};

struct node { 
    int data; 
    struct node* next; 
}; 


/// cs0019_malloc(sz, file, line)
///    Return a pointer to `sz` bytes of newly-allocated dynamic memory.
///    The memory is not initialized. If `sz == 0`, then cs0019_malloc may
///    either return NULL or a unique, newly-allocated pointer value.
///    The allocation request was at location `file`:`line`.

void *cs0019_malloc(size_t sz, const char *file, int line) {
  (void)file, (void)line; // avoid uninitialized variable warnings
  // Your code here.

  //If it fails
  if(sz >= (size_t)-1 - 150){
    failed += 1;
    failed_size += sz;
    return NULL;
  }
  else{
    //Initialize structure
    struct metadata data = {sz};

    //Creates a metadata pointer that points to the base_malloc
    char* base = (char*) base_malloc(metadata_size + sz);

    //Dereferences that pointer and sets to value of data
    struct metadata *ptr_metadata = (struct metadata *) base; 
    *ptr_metadata = data;

    //printf("Pointer malloc = %p\n",ptr_metadata);
    //printf("Pointer malloc = %p\n",base + metadata_size);


    total_malloc += 1;
    activeAlloc += 1;
    activeAlloc_size += sz;
    total_size += sz;

    if(heap_min == NULL){
      heap_min = base + metadata_size;
    }
    else if (heap_min > base + metadata_size){
      heap_min = base + metadata_size;
    }

    if(heap_max == NULL){
      heap_max = base + metadata_size + sz;
    }
    else if (heap_max < base + metadata_size + sz){
      heap_max = base + metadata_size + sz;
    }


    // if(head == NULL){
    //   head = (struct node*)malloc(sizeof(struct node)); 
    //   head->data = (int) (base + metadata_size);
    // }
    // else{
    //   struct node *traverse = head; 
    //   //finds the last element
    //   while (traverse->next != NULL) { 
    //     traverse = traverse->next;
    //   }
      
    //   struct node *temp = (struct node*)malloc(sizeof(struct node));
    //   temp->data = (int) (base + metadata_size);
    //   traverse->next = temp;

    // }

    //Returns a pointer to the original place

    return (base + metadata_size);
  }
 
  return base_malloc(sz);
}

/// cs0019_free(ptr, file, line)
///    Free the memory space pointed to by `ptr`, which must have been
///    returned by a previous call to cs0019_malloc and friends. If
///    `ptr == NULL`, does nothing. The free was called at location
///    `file`:`line`.

void cs0019_free(void *ptr, const char *file, int line) {
  (void)file, (void)line; // avoid uninitialized variable warnings

  // Your code here.
  if (ptr != NULL){
    // int not_found = 0;

    // //Makes sure ptr is freeable else exits
    // struct node *checker = head; 
    // while (checker != NULL) { 
    //   checker = checker->next;
    //   if(checker == ptr){
    //     not_found = 1;
    //   }
    // }

    // if(not_found){
    //   printf("MEMORY BUG: test017.c:9: invalid free of pointer %p", ptr);
    // }
    if((char*) ptr < heap_min || (char *)ptr > heap_max){
      printf("MEMORY BUG: test017.c:9: invalid free of pointer %p, not in heap\n", ptr);
    }
    else{


      //Creates a metadata pointer
      char* new_ptr =  ptr; 
      //printf("Pointer new_ptr = %p\n",new_ptr);

      new_ptr = new_ptr - metadata_size;

      //printf("Pointer new_ptr = %p\n",new_ptr);

      struct metadata *ptr_metadata = (struct metadata *) new_ptr; 
      
      //Dereferences that pointer
      size_t alloc_size = ptr_metadata->size;

      //printf("%d : this is alloc_size\n",alloc_size);

      activeAlloc -= 1;
      activeAlloc_size -= alloc_size;

      // //Goes through until it finds the node before the one we want to remove
      // struct node *traverse = head; 
      // while (traverse->next != ptr) { 
      //   traverse = traverse->next;
      // }
      

      // struct node *temp = (struct node*)malloc(sizeof(struct node));
      // temp = traverse->next;

      // //Sets the next one to skip
      // traverse->next = temp->next;
      base_free(ptr);
    }
  }
  
}

/// cs0019_realloc(ptr, sz, file, line)
///    Reallocate the dynamic memory pointed to by `ptr` to hold at least
///    `sz` bytes, returning a pointer to the new block. If `ptr` is NULL,
///    behaves like `cs0019_malloc(sz, file, line)`. If `sz` is 0, behaves
///    like `cs0019_free(ptr, file, line)`. The allocation request was at
///    location `file`:`line`.

void *cs0019_realloc(void *ptr, size_t sz, const char *file, int line) {
  
  void *new_ptr = NULL;

  // if(ptr != NULL){
  //  for(int i=0; i < 5;i++){
  //    printf("%d here",*((char*)ptr+i));
  //  }
  // }

  if (sz) {
    //If there is a size then mallocs 
    new_ptr = cs0019_malloc(sz, file, line);
  }

  //A realloc where a new size is needed
  if (ptr && new_ptr) {
  // Copy the data from `ptr` into `new_ptr`.
  // To do that, we must figure out the size of allocation `ptr`.
  // Your code here (to fix test014).


    char* temp_ptr = (char* ) ptr;
    temp_ptr = temp_ptr - metadata_size;


    struct metadata *ptr_metadata = (struct metadata *) temp_ptr; 
    //Dereferences that pointer
    size_t alloc_size = ptr_metadata->size;
    

    //Copies from old pointer to the new pointer
    memcpy(new_ptr,ptr,alloc_size);
    
  }

  cs0019_free(ptr, file, line);
  return new_ptr;
}

/// cs0019_calloc(nmemb, sz, file, line)
///    Return a pointer to newly-allocated dynamic memory big enough to
///    hold an array of `nmemb` elements of `sz` bytes each. The memory
///    is initialized to zero. If `sz == 0`, then cs0019_malloc may
///    either return NULL or a unique, newly-allocated pointer value.
///    The allocation request was at location `file`:`line`.

void *cs0019_calloc(size_t nmemb, size_t sz, const char *file, int line) {
// Your code here (to fix test016).

  if(nmemb >= ((size_t)-1 - 150)/sz){
    failed += 1;
    failed_size += sz;
    return NULL;
  }

  void *ptr = cs0019_malloc(nmemb * sz, file, line);

  if (ptr) {
    memset(ptr, 0, nmemb * sz);
  }
  return ptr;
}

/// cs0019_getstatistics(stats)
///    Store the current memory statistics in `*stats`.

void cs0019_getstatistics(struct cs0019_statistics *stats) {
  // Stub: set all statistics to enormous numbers
  memset(stats, 255, sizeof(struct cs0019_statistics));
  // Your code here.

  stats->nactive = activeAlloc;
  stats->active_size = activeAlloc_size;
  stats->ntotal = total_malloc;
  stats->total_size = total_size;
  stats->nfail = failed;
  stats->fail_size = failed_size;
  stats->heap_min = heap_min;
  stats->heap_max = heap_max;

}

/// cs0019_printstatistics()
///    Print the current memory statistics.

void cs0019_printstatistics(void) {
  struct cs0019_statistics stats;
  cs0019_getstatistics(&stats);

  printf("malloc count: active %10llu   total %10llu   fail %10llu\n",
         stats.nactive, stats.ntotal, stats.nfail);
  printf("malloc size:  active %10llu   total %10llu   fail %10llu\n",
         stats.active_size, stats.total_size, stats.fail_size);
}

/// cs0019_printleakreport()
///    Print a report of all currently-active allocated blocks of dynamic
///    memory.

void cs0019_printleakreport(void) {
// Your code here.
}

/// cs0019_printheavyhitterreport()
///    Print a report of all the heavy hitters as described
///    in the coursework handout.

void cs0019_printheavyhitterreport(void) {
// Your code here.
}

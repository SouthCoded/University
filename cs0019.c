#define CS0019_DISABLE 1
#include "cs0019.h"
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define metadata_size sizeof(size_t)+sizeof(size_t)+sizeof(size_t)//24 dec

int total_malloc = 0;
size_t total_size = 0;
int activeAlloc = 0;
int activeAlloc_size = 0;
int failed = 0;
int failed_size = 0;
char* heap_min = (char*) 0xfffffffffffff;
char* heap_max = (char*) 0x0000000000000;
struct node* head = NULL; 
struct node* tail = NULL;

struct TM_node* TM_head = NULL;
struct TM_node* TM_tail = NULL;

struct metadata 
{ 
   size_t size;
   const char* file;
   int line; 
};

struct node { 
    char* data; 
    struct node* next; 
}; 


struct TM_node { 
    struct metadata data; 
    struct TM_node* next; 
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
    struct metadata data = {sz,file,line};

    //Creates a metadata pointer that points to the base_malloc
    char* base = (char*) base_malloc(metadata_size + sz + 4);

    //Dereferences that pointer and sets to value of data
    struct metadata *ptr_metadata = (struct metadata *) base; 
    *ptr_metadata = data;

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

    //Setting up linked list
    if(head == NULL){
      head = (struct node*)malloc(sizeof(struct node)); 
      head->data = base + metadata_size;
      head->next = NULL;
      tail = head;
    }
    else{
      struct node* traverse = tail;
      struct node *temp = (struct node*)malloc(sizeof(struct node));
      temp->next = NULL;
      temp->data = base + metadata_size;
      traverse->next = temp;
      tail = temp;
    }

    if(TM_head == NULL){

      TM_head = (struct TM_node*)malloc(sizeof(struct TM_node));
      TM_head->data = data;
      TM_head->next = NULL; 
      TM_tail = TM_head;
    }
    else{
      struct TM_node* TM_traverse = TM_tail;
      struct TM_node *TM_temp = (struct TM_node*)malloc(sizeof(struct TM_node));
      TM_temp->next = NULL;
      TM_temp->data = data;
      
      TM_traverse->next = TM_temp;

      TM_tail = TM_temp;

    }

    int* canary = (int*)(base+metadata_size+sz);

    *canary = 0xAAAA;

    //printf("%p metadata\n",base);
    //printf("%p malloc\n",base + metadata_size);
    //Returns a pointer to the original place
    return (base + metadata_size);
  }
 
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
    if((char*) ptr < heap_min || (char *)ptr > heap_max){
      printf("MEMORY BUG: %s:%d: invalid free of pointer %p, not in heap\n",file,line,ptr);
    }
    else{

      int not_found = 1;

      //Makes sure ptr exists in linkedlist
      struct node *checker = head;   

      while (checker != NULL) { 
        if(checker->data == ptr){
          not_found = 0;
        }
        checker = checker->next;
      }

      if(not_found){
        printf("MEMORY BUG: %s:%d: invalid free of pointer %p, not allocated\n",file,line,ptr);

        struct node *traverse = head; 

        while (traverse != NULL) { 
          //Creates a metadata pointer
          char* new_ptr =  traverse->data; 
          new_ptr = new_ptr - 0x18;  
          struct metadata *ptr_metadata = (struct metadata *) new_ptr; 
          //Dereferences that pointer
          size_t alloc_size = ptr_metadata->size;

          if((char*) ptr < (new_ptr+alloc_size) && (char*) ptr > new_ptr){
            int difference = (char*) ptr - traverse->data;
            printf("  %s:%d: %p is %d bytes inside a %ld byte region allocated here\n",file,line-1,ptr,difference,alloc_size);
          }          
          traverse = traverse->next;

        }
      } 
      else{

        //Creates a metadata pointer
        char* new_ptr =  ptr; 
        
        new_ptr = new_ptr - 0x18;  

        struct metadata *ptr_metadata = (struct metadata *) new_ptr; 
      
        //Dereferences that pointer
        size_t alloc_size = ptr_metadata->size;

        if(*((int*)(ptr+alloc_size)) != 0xAAAA){
          printf("MEMORY BUG: %s:%d: detected wild write during free of pointer %p\n",file,line,ptr);
        }

        activeAlloc -= 1;
        activeAlloc_size -= alloc_size;

        struct node* new_head = NULL; 
        struct node* new_tail = NULL;
   

        //If head is the one that contains the data
        if(head->data == ptr){
          if(head->next != NULL){
            //Create the new head
            new_head = (struct node*)malloc(sizeof(struct node));
            new_head->next = NULL;
            new_head->data = NULL;

            //Get the next node
            struct node *nexter = head->next;

            //Transfer data to the new head
            new_head->data = nexter->data;

            struct node *traverse = nexter->next; 
            //Goes through rest of the list to copy
            while (traverse != NULL) { 
              //New_head already created so we need a node to cycle through new_head until it is null
              struct node *cycle = new_head;

              while (cycle->next != NULL) {
                cycle = cycle->next;
              }
              
              //Now cycle contains the last node
              //Create a node to add onto the end of our new linked list
              struct node *temp = (struct node*)malloc(sizeof(struct node));
              temp->data = traverse->data;
              temp->next = NULL;
              cycle->next = temp;

              new_tail = temp;
              
              traverse = traverse->next;
            }
            
          }
          else{
            //Resets if head is the only data
            head = NULL;
            new_tail = NULL;
          }
        }
        else{

          //Goes through the entire linked list
          struct node *traverse = head; 

          while (traverse != NULL) { 

            //If new_head isn't created yet, we create it - won't have the data in the head as checked before 
            if(new_head == NULL){
                new_head = (struct node*)malloc(sizeof(struct node));
                new_head->data = traverse->data;
                new_head->next = NULL;
                new_tail = new_head;
            }
            else{              
              
              //New_head already created so we need a node to cycle through new_head until it is null
              struct node *cycle = new_head;
              
              while (cycle->next != NULL) {
                cycle = cycle->next;
              }

              if(traverse->data != ptr){
                //Now cycle contains the last node
                //Create a node to add onto the end of our new linked list
                struct node *temp = (struct node*)malloc(sizeof(struct node));
                temp->data = traverse->data;
                temp->next = NULL;
                cycle->next = temp;

                new_tail = temp;
              }
            }
            traverse = traverse->next;
          }
        }

        head = new_head;
        tail = new_tail;


        base_free(new_ptr);

      }

      
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

  if(ptr != NULL){
   if(((char*) ptr < heap_min || (char *)ptr > heap_max)){
        printf("MEMORY BUG: %s:%d: invalid free of pointer %p, not in heap\n",file,line,ptr);
        return NULL;
    }
    else{

      int not_found = 1;

      //Makes sure ptr exists in linkedlist
      struct node *checker = head;   

      while (checker != NULL) { 
        if(checker->data == ptr){
          not_found = 0;
        }
        checker = checker->next;
      }

      if(not_found){
        printf("MEMORY BUG: %s:%d: invalid free of pointer %p, not allocated\n",file,line,ptr);
        return NULL;
      } 

    }
  }
 

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
    temp_ptr = temp_ptr - 0x18;


    struct metadata *ptr_metadata = (struct metadata *) temp_ptr; 
    //Dereferences that pointer
    size_t alloc_size = ptr_metadata->size;
    
    if(alloc_size > sz){
      memcpy(new_ptr,ptr,sz);
    }
    else{
       memcpy(new_ptr,ptr,alloc_size);
    }
    //Copies from old pointer to the new pointer
   

    //printf("Check found %p\n",(new_ptr+alloc_size));
    //printf("%x\n", *((int*)(new_ptr+alloc_size)));

    
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
  
  if(head != NULL){

    struct node *traverse = head;   

      while (traverse != NULL) { 

        //Creates a metadata pointer
        char* new_ptr =  traverse->data; 
        //printf("Pointer new_ptr = %p\n",new_ptr);

        new_ptr = new_ptr - 0x18;  

        //printf("Pointer new_ptr = %p\n",new_ptr);

        struct metadata *ptr_metadata = (struct metadata *) new_ptr; 
      
        //Dereferences that pointer
        size_t alloc_size = ptr_metadata->size;
        const char* file = ptr_metadata->file;
        int line = ptr_metadata->line;

        printf("LEAK CHECK: %s:%d: allocated object %p with size %ld\n",file,line,traverse->data,alloc_size);
       
        traverse = traverse->next;
      }

    

  }


}

/// cs0019_printheavyhitterreport()
///    Print a report of all the heavy hitters as described
///    in the coursework handout.

void cs0019_printheavyhitterreport(void) {
// Your code here.

  struct TM_node *TM_traverse = TM_head;   

  struct TM_node *traverse = TM_head;

  struct metadata array[100000] = {{0,"",0}};

  while (traverse != NULL) { 

    int random = rand();

    if(random % 100 == 0){

      //Get data from the linked list of the line and size of malloc
      int new_line = traverse->data.line;
      size_t new_size = traverse->data.size;
      
      if(array[new_line].line == 0){
        struct metadata new_data = {new_size,traverse->data.file,traverse->data.line};

        array[new_line] = new_data;
      }
      else{
        struct metadata new_data = array[new_line];

        new_data.size += new_size;
        array[new_line] = new_data;
      }
    }



    traverse = traverse->next;
  }

  for(int x = 0;x < 5; x++){
    for(int y = x+1; y < 100000; y++){
       if(array[x].size < array[y].size){
          struct metadata temp = array[x];
          array[x] = array[y];
          array[y] = temp; 
        }
    }
  }

  for(int x = 0;x < 5; x++){
    float percent = ((float)array[x].size/(float)total_size);
    if(percent > 0.2){
      printf("HEAVY HITTER: %s:%d: %ld bytes (~%2.1f%)\n",array[x].file,array[x].line,array[x].size,percent*100);
    }
  }

     



  

}


#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <assert.h>
#include "ticker_prot.h"
#include "minirpc.h"
#include <rpc/svc.h>
#include <sys/queue.h>


char *progname;
u_int32_t my_id;		/* This server's unique ID */
int nothers;			/* Number of other servers */
struct sockaddr_in **others;	/* Addresses of the other servers,
				 * followed by a NULL pointer */
int logical_clock = 0;


void ticker_prog_1 (struct svc_req *rqstp, SVCXPRT *transp);

struct requests {
  msg_t message;
  int time;
  int process_id;
  int physical_time;
  struct requests* next;
};

struct requests* head = NULL; 
struct requests* tail = NULL;

static struct requests* request_alloc(void) {
    struct requests* c = (struct requests*) malloc(sizeof(struct requests));
    c->message = (msg_t*) malloc(sizeof(msg_t)*10);
    c->time = 0;
    c->process_id = 0;
    c->physical_time = 0;
    c->next = NULL;
    return c;
}

void print_queue(struct requests *node){

  FILE *fp;
  fp = fopen("./server123.txt", "a");

  fprintf(fp,"Calling print\n");

  int c = 0;

  struct requests* first_message = head;
  struct requests *id_list[100] = {0};


  //All messages
  while(node != NULL){
    
    fprintf(fp,"%s message and logical time %d and elapsed time %d and process_id %d\n",node->message,node->time,node->physical_time,node->process_id);
    
    int d = 0;
    int contains = 0;

    //Goes through ID list, searching for process id
    while(id_list[d] != 0){
      if(id_list[d] == (int)(node->process_id)){
        contains = 1;
      }
      d++;
    }

    if(contains == 0){
      id_list[c] = (int)node->process_id;
      c++;
    }

    node = node->next;
  }

  //SORT ID_LIST
  for(int h = 0; h < c; h++){
    for(int k = h; k < c; k++){
      if(id_list[k] < id_list[h]){
        int temp = (int)id_list[h];
        id_list[h] = id_list[k];
        id_list[k] = temp;
      }
    }
  }

  //Final Ordering
  struct requests *final_queueHead = NULL;
  struct requests *final_queue = NULL;
  

  //AT THIS TIME
  for(int j=0;j<=logical_clock;j++){

    //fprintf(fp,"At this time %d ",j);
    //AT THIS PROCESS
    for(int l=0;l<c;l++){
    
      //fprintf(fp,"At this process %d ",l);
      //GOES THROUGH EVERYONE
      struct requests* checker = head;
      
      while(checker != NULL){
        
        //fprintf(fp,"this value %s ",checker->message);

        if(j == checker->time && id_list[l] == checker->process_id){
          
          //fprintf(fp,"was copied\n");
          struct requests *temp = request_alloc();
          strcpy(temp->message,checker->message);
          temp->time = checker->time;
          temp->process_id = checker->process_id;
          temp->physical_time = checker->physical_time;
          temp->next = NULL;


          if(final_queueHead == NULL){
            final_queueHead = temp;
            final_queue = temp;
          }
          else{
            final_queue->next = temp;
            final_queue = final_queue->next;
          }
        }
        
        checker = checker->next;
      }
    }
  }

  final_queue = final_queueHead;
  fprintf(fp,"ALL OF FINAL_QUEUE ------------------------------ this is first message %s\n", head->message);
  while(final_queue != NULL){
    fprintf(fp,"%s message and logical time %d and elapsed time %d and process_id %d\n",final_queue->message,final_queue->time,final_queue->physical_time,final_queue->process_id);
    final_queue = final_queue->next;
  }
  fprintf(fp,"FINISHED FINAL_QUEUE ------------------------------\n");

  struct requests *delete_queueHead = NULL;
  struct requests *delete_queue = NULL;
  
  final_queue = final_queueHead;

  //print from final_queue until first message
  while(final_queue != NULL){
    
    if(final_queue->physical_time == (first_message->physical_time)+1){
      final_queue = NULL;
    }
    else{
      
      fprintf(fp,"%s PRINTED OUT\n",final_queue->message);
      printf("%s\n",final_queue->message);
      struct requests *temp = request_alloc();
      strcpy(temp->message,final_queue->message);
      temp->time = final_queue->time;
      temp->process_id = final_queue->process_id;
      temp->physical_time = final_queue->physical_time;
      temp->next = NULL;

      if(delete_queueHead == NULL){
        delete_queue = temp;
        delete_queueHead = temp;
      }
      else{
        delete_queue->next = temp;
        delete_queue = delete_queue->next;
      }

      final_queue = final_queue->next;
    }
  }

  delete_queue = delete_queueHead;

  fprintf(fp,"This is head value %s\n",head->message);

  //Goes through delete_queue and deletes messages in the head queue
  while(delete_queue != NULL){

    node = head;
    struct requests *previous_node = NULL;

    fprintf(fp,"This is head %x \n",head);
    fprintf(fp,"This is delete queue value %s\n",delete_queue->message);

    //Goes through req queue
    while(node != NULL){

      fprintf(fp,"This is node %x with value %s and next value %x\n",node,node->message,node->next);
      if(strcmp(delete_queue->message,node->message) == 0){
        fprintf(fp,"This passes\n");

        if(strcmp(delete_queue->message,head->message) == 0){
          head = node->next;
          previous_node = NULL;
          fprintf(fp,"This runs and head is %x\n",head);

        }
        else if(previous_node != NULL){
          previous_node->next = node->next;
        }
      }
      else{
        previous_node = node;
      }
      node = node->next;
    }
    delete_queue = delete_queue->next;
  }

  if(head == NULL){
    fclose(fp);
    tail = NULL;
    want_timer = 0;
  }
}

submit_result *
ticker_submit_1_svc (submit_args *argp, struct svc_req *rqstp)
{
  static submit_result result;

  struct requests* temp_request = request_alloc();
  
  want_timer = 1;

  strcpy(temp_request->message,argp->msg);
  temp_request->time = logical_clock;
  logical_clock += 1;
  temp_request->process_id = my_id;
  temp_request->physical_time = elapsed;

  if(head == NULL){
    head = temp_request;
    tail = temp_request;
  }
  else{
    tail->next = temp_request;
    tail = temp_request;
  }

  rpc_broadcast(others,TICKER_PROG,TICKER_VERS,TICKER_REQUEST_RESOURCE,xdr_request_resource_args,temp_request);

  result.ok = TRUE;
  return (&result);
}

void *
ticker_request_resource_1_svc (request_resource_args *argp, struct svc_req *rqstp)
{
  //printf("%s (XXX Copied statement) and logical clock is %d\n",argp->message,argp->time);

  struct requests* temp_request = request_alloc();

  strcpy(temp_request->message,argp->message);
  temp_request->time = (argp->time);

  want_timer = 1;

  if(logical_clock <= (argp->time)){
    logical_clock = (argp->time) + 1;
  }
  else{
    logical_clock += 1;
  }

  temp_request->process_id = (argp->process_id);
  temp_request->physical_time = elapsed;

  if(head == NULL){
    head = temp_request;
    tail = head;
  }
  else{
    tail->next = temp_request;
    tail = temp_request;
  }
  
  return &my_id;
}

/*
 * This function gets called once per second, if you set the global
 * variable want_timer to a positive value.
 *
 * You should use this to print out trades in order.  (You have to
 * delay printing a trade until you know you have heard of and printed
 * any trades that happened before that trade.)
 */
void
timer (void)
{
  /*
   7 seconds pass inbetween - order has to stand, will anws due to ordering
   13 seconds, have to print
   all requests will be received within 3 seconds

   can't print all at once - have to continously print
  */

  //Checks first packet received, prints that and any packets before
  if(elapsed-(head->physical_time) >= 2){
    print_queue(head);
  }


}

/*
 *  You don't have to change anything below here
 */

static void
init_others (int no, char **av)
{
  int i;
  struct hostent *hp;
  int failed = 0;

  nothers = no;

  others = malloc ((nothers + 1) * sizeof (others[0]));
  if (!others) {
    fprintf (stderr, "out of memory\n");
    exit (1);
  }
  others[nothers] = NULL;	/* So end of list is NULL */

  for (i = 0; i < nothers; i++) {
    others[i] = malloc (sizeof (*others[i]));
    if (!others[i]) {
      fprintf (stderr, "out of memory");
      exit (1);
    }
    bzero (others[i], sizeof (*others[i]));
    others[i]->sin_family = AF_INET;
    hp = gethostbyname (*av++);
    if (!hp) {
      fprintf (stderr, "%s: could not find address of host %s\n",
	       progname, av[-1]);
      failed = 1;
    }
    others[i]->sin_addr = *(struct in_addr *) hp->h_addr;
    others[i]->sin_port = htons (atoi (*av++));
  }

  if (failed)
    exit (1);
}

static void usage (void) __attribute__ ((noreturn));
static void
usage (void)
{
  fprintf (stderr, "usage: %s my-id my-port host1 port1 [host2 port2 ...]\n",
	   progname);
  exit (1);
}

int
main (int argc, char **argv)
{
  int my_sock;
  SVCXPRT *transp;

  if ((progname = strrchr (argv[0], '/')))
    progname++;
  else
    progname = argv[0];

  if (argc < 3 || (argc - 3) % 2)
    usage ();

  my_id = atoi (argv[1]);
  my_sock = mkudpsock (atoi (argv[2]));
  init_others ((argc - 3) / 2, argv + 3);

  if (!(transp = svcudp_create (my_sock))) {
    fprintf (stderr, "cannot create UDP service\n");
    exit (1);
  }
  if (!svc_register (transp, TICKER_PROG, TICKER_VERS, ticker_prog_1, 0)) {
    fprintf (stderr, "failed to register RPC program\n");
    exit (1);
  }

  setvbuf (stdout, NULL, _IOLBF, 0);
  rpc_run ();
}

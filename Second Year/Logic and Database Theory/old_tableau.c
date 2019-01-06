#include <stdio.h> 
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */



int Fsize=50; /*maximum formula length*/
int cases =10;/* number of formulas expected in input.txt*/
int i;/* in case you need it */
int ThSize=100;/* maximum size of set of formulas*/
int TabSize=500; /*maximum length of tableau queue*/



/* A set will contain a list of words. Use NULL for emptyset.  */
struct set{
  char *item;/*first word of non-empty set*/
  struct set *tail;/*remaining words in the set*/
};

/* A tableau will contain a list of pointers to sets (of words).  Use NULL for empty list.*/
struct tableau {
  struct set * S; /* pointer to first set in non-empty list */
  struct tableau *rest; /*list of pointers to other sets*/
};


char valid(char *g){

  char h[100] = "";
  int j = 0;

  //printf("Valid %s\n",g);


  for(int x = 0; x < strlen(g);x++){
    if(g[x] == '-'){
      if(g[x+1] == '-'){
     
      }
      else if(g[x+1] != 'p' && g[x+1] != 'q' && g[x+1] != 'r' &&g[x+1] != 'T'){
        return 'F';
      }
    }
  }
  
  //COPYING FUNCTION WITHOUT '-'
  int t = 0;
  for(int x = 0; x < strlen(g);x++){
    if(g[x] != '-' && g[x] != '(' && g[x] != ')'){
     h[t] = g[x];
     t++;
    }
  }

  //printf("Without %s\n",h);

  if(strlen(h) !=3){
    return 'F';
  }

  if(h[0] != 'p' && h[0] != 'q' && h[0] != 'r'  && h[0] != 'T'){
    return 'F';
  }
  if(h[2] != 'p' && h[2] != 'q' && h[2] != 'r'  && h[2] != 'T'){
    return 'F';
  }
  if(h[1] != 'v' && h[1] != '>' && h[1] != '^' ){
    return 'F';
  }

  return 'T';

}

int paraCheck(char *g){
  int left_para = 0;
  int right_para = 0;
  for(int i = 0 ; i < strlen(g);i++){
    if(g[i] == '('){
      left_para++;
    }
    if(g[i] == ')'){
      right_para++;
    }
  }

  if(left_para != right_para){
    return 0;
  }

  return -1;
}

int formula(char *g){

  int paraCheckInt = paraCheck(g);

  if(paraCheckInt == 0){
    return 0;
  }

  char equation[strlen(g)];
  char h[100] = "";
  int j = 0;

 
  strcpy(equation,g);


  for(int i = 0; i < strlen(equation);i++){
    
    if(equation[i] == '('){
      int placement = i;
      h[j] = equation[i];
      i++; j++;
      h[j] = equation[i];

      //Memorizes equation, putting the () into another array 
      while((equation[i] != ')' && equation[i] != '(') && i < strlen(equation)){
        h[j+1] = equation[i+1];
        i++; j++;
      }

      if(equation[i] == '('){
        memset(h, 0, sizeof(h));
        i = placement;
        j = 0;
      }
      if(equation[i] == ')'){
        char a = valid(h);
        if(a == 'F'){
          return 0;
        }
        char temp[100] = "";
        int t = 0;
        
        //Removing the () and replacing with T
        for(int z = 0; z < strlen(equation);z++){
          if(z < placement){
            temp[t] = equation[z];
            t++;
          }
          if(z == i){
            temp[t] = a;
            t++;

          }
          if(z > i){
            temp[t] = equation[z];
            t++;
          }
        }

        strcpy(equation,temp);

        memset(h, 0, sizeof(h));
        j = 0;
        i = -1;
      }
    }
    //printf("%s\n",equation);
  }

  return 3;
}

//Defrencing a pointer, passes in a value
int parse(char *g){

  if(g[0] == '-'){
    
    int heavy = 0;
    while(g[heavy] == '-'){
      heavy++;
    }
    if(g[heavy] == '('){
      if(formula(g) == 3){
        return 2;
      }
      else{
        return 0;
      }
    }
    else if(g[heavy] != 'p' && g[heavy+1] != 'q' && g[heavy+1] != 'r'){
      return 0;
    }
    return 2;
   
  }
  else if(strlen(g) == 1 && (g[0] == 'p' || g[0] == 'q' || g[0] == 'r')){
    return 1;
  }
  else{
    return formula(g);
  }

}

int finder(char *tobeFound){

    int found = -1;

    char equation[100] = "";

    strcpy(equation,tobeFound);

    for(int i = 0; i < strlen(equation);i++){

      if(equation[i] == '('){
        int placement = i;
        i++;

        //Memorizes equation, putting the () into another array 
        while((equation[i] != ')' && equation[i] != '(') && i < strlen(equation)){
          i++; 
        }

        if(equation[i] == '('){
          i = placement;
        }
        else if(equation[i] == ')'){
          int last = 0;
        
          for(int t = 0; t < strlen(equation);t++){
            if(equation[t] == '^' || equation[t] == '>' || equation[t] == 'v'){
              last++;
            }
          }

          if(last > 1){
            //Removing the equation and replace with X
            for(int z = 0; z < strlen(equation);z++){
              if((z <= i) && (z >= placement)){
                equation[z] = 'X';
              }
            }
            i = -1;
          }
          if(last == 1){
            for(int t = 0; t < strlen(equation);t++){
              if(equation[t] == '^' || equation[t] == '>' || equation[t] == 'v'){
                found = t;
                return found;
              }
            }
          }
        }
      }
    }

    return found;

}

char* notReducer(char *reduce){

      char* temp = malloc(Fsize);

      int incr = 0;

      while(reduce[incr] == '-'){
        incr ++;
      }

      if(incr%2 == 0 && incr > 0){
        int ab = 0;

        for(int i = incr; i < strlen(reduce);i++){
          temp[ab] = reduce[i];
          ab++;
        }
       return temp;
      }
      else if(incr%2 == 1){
        int ab = 0;

        for(int i = incr-1; i < strlen(reduce);i++){
          temp[ab] = reduce[i];
          ab++;
        }
       return temp;
      }
      
      return reduce;
    
}

void addToEnd(struct tableau *t, char *addition){

    struct set *temp = malloc(Fsize);
    struct set *current = t->S;

    if(t->S->item == ""){
      t->S->item = addition;
    }
    else{
      while(current->tail != NULL){
        current = current->tail;
      }

    temp->item = addition;
    temp->tail = NULL;
    current->tail = temp;
    }
    
}

void startNewBranch(struct tableau *t,char *addition){

    struct set *temp = malloc(Fsize);
    struct tableau *nTab = malloc(Fsize);

    while(t->rest != NULL){
      t = t->rest;
    }

    temp->item = addition;
    temp->tail = NULL;

    nTab->S = temp;
    nTab->rest = NULL;

    t->rest = nTab;

}

struct tableau * getLeftChild(struct tableau *t, struct set *current){

  printf("This is current value %s\n",current->item);

  int count = 0;
  int leftChild;

  struct tableau *body = t;

  int final = -1;

  //finds left tableau with the set desired
  while(body != NULL && final == -1){

      while(body->S != NULL){

        if(strcmp(body->S->item,current->item) == 0){
          final = count;    
        }
        body->S = body->S->tail;
      }
      if (final == -1){
        count ++;
        body = body->rest;
      }

  }
  if(final != -1){
    leftChild = (2*final) + 1;
 

  count = 0;
  printf("This is count and leftchild %d %d\n",count,leftChild);

  body = t;

  //finding right set
  while(body->rest != NULL && count != leftChild){
        count++;
        body = body->rest;
  }

  printf("FOUND IT %s\n",body->S->item);
  }
  return body;
}

struct tableau * getRightChild(struct tableau *t, struct set *current){

  printf("This is current value %s\n",current->item);

  int count = 0;
  int rightChild;

  struct tableau *body = t;

  int final = -1;

  //finds left tableau with the set desired
  while(body != NULL && final == -1){

      while(body->S != NULL){ 

        printf("H %s , %s \n",body->S->item,current->item);
        if(strcmp(body->S->item,current->item) == 0){
          final = count;    
        }
        body->S = body->S->tail;
      }
      if (final == -1){
        count ++;
        body = body->rest;
      }

  }

  rightChild = (2*final) + 2;

  count = 0;
  printf("This is count and rightChild %d %d\n",count,rightChild);

  body = t;

  //finding right set
  while(body->rest != NULL && count != rightChild){
        count++;
        body = body->rest;
  }

  printf("FOUND IT %s\n",body->S->item);

  return body;
}

int hasLeftChild(struct tableau *t, struct set *current){

  printf("HasLeftChild %s\n",current->item);
  printf("This is t %x\n",t->S);

  int count = 0;
  int leftChild;


  struct tableau *temp = t;



  int final = -1;

  //finds left tableau with the set desired
  while(temp != NULL && final == -1){

      while(temp->S != NULL){

        if(strcmp(temp->S->item,current->item) == 0){
          final = count;    
        }
        
        temp->S = temp->S->tail;
        
      }
      if (final == -1){
        printf("This runs?");
        count ++;
        temp = temp->rest;
      }

  }
  if(final != -1){
    
    leftChild = (2*final) + 1;
   
    count = 0;
    printf("This is count and leftchild %d %d\n",count,leftChild);
    printf("This is t %x\n",t->S);

    struct tableau *new = t;

    printf("This fails %x\n", new->S);

    //finding right set
    while(temp->rest != NULL && count != leftChild){
          count++;
          temp = temp->rest;
    }

    printf("FOUND IT %s\n",temp->S->item);
  }


  if(count == leftChild && temp->S->item != ""){
    return 1;
  }
  else{
    return 0;
  }

}

int isAChild(struct tableau *head,struct tableau *t){

  struct tableau * body = head; //marks the body of the tab

  int count = 0;
  int parent;

  int final = 0;

  //finds right tableau with the set desired
  while(body->rest != NULL && final != 0){
      if(body->S->item == t->S->item){
        final = count;
      }
      if(final == 0){
        body = body->rest;
      }
      else{
        count ++;
      }
  }

  parent = (final-1)/2;


  count = 0;

  //finding right set
  while(head->rest != NULL && count != parent){
        count++;
        head = head->rest;
  }

  if(count == parent && final != 0 && final%2 ==0){
    return 2;
  }
  else if (count == parent && final != 0){
    return 1;
  }
  else{
    return 0;
  }
}

void readTab(struct tableau *t){
   while(t != NULL){
      printf("NEW TAB\n");
      struct set *temp = t->S;
      while(temp != NULL){
          printf("This is the value's %s\n",temp->item);
          temp = temp->tail;
      }           
      t = t->rest;
    }
}

void complete(struct tableau *t){


    struct tableau * head = malloc(Fsize);
    struct set *fake = malloc(Fsize);
    fake->item = "";
    fake->tail = NULL;

    head->S = fake;
    head->rest = t;



    struct tableau * body = t;

    while(body != NULL){
  
        char* equation = "";
        int dumb = 0;
        
        struct set *current = body->S; //address of current points to t->S, equation points to current ->item;

        //creates an empty left and right child for each tab
        if(hasLeftChild(body,current) == 0 && current->item != ""){
          startNewBranch(body,"");
          startNewBranch(body,"");
        }        

        if(current->item == ""){
          dumb = 1;
        }

        while(current != NULL && dumb == 0){

          char* reduced = malloc(Fsize);

          equation = current->item; //equation points to current->items address

          strcpy(reduced,notReducer(equation));  //reduced is still pointing to its own address
          
          printf("Equation %s \n",equation);

          if(strcmp(equation,reduced) != 0){ //equation and reduced are still pointing to their own address

            printf("Reduce Equation %s\n",reduced);

            addToEnd(body,reduced);
          }
          else{

            int found = finder(equation);

            //This means that it is a literal, so should move to another branch if there is one
            if(found == -1){
              printf("Literal %s\n\n",current->item);
              
            } // This means that it can be split further, so continue
            else{
             
              int ls = 0;
              int rs = 0;
              int neg = 0;
              int leftbracket = 0;

              char* left = malloc(Fsize);
              char* right = malloc(Fsize);
              char begin[100] = "";

              if(equation[found] == '>'){

                if(equation[0] != '-'){
                  char leftonly[100] = "";
                  leftonly[0] = '-';

                  while(equation[neg] != '('){
                    begin[neg] = equation[neg];
                    leftonly[neg+1] = equation[neg];
                    neg ++;
                  }


                  strcpy(left,leftonly);
                  strcpy(right,begin);

                  ls++;
                }
                else{
                  char rightonly[100] = "";
                  rightonly[0] = '-';

                  strcpy(left,begin);
                  strcpy(right,rightonly);

                  rs++;
                }

              }
              else{

                while(equation[neg] != '('){
                  begin[neg] = equation[neg];
                  neg ++;
                }

                strcpy(left,begin);
                strcpy(right,begin);

              }
              
              ls += neg;
              rs += neg;

              for(int i = 0 ; i < strlen(equation);i++){  

                 if(i < found){

                  if(leftbracket == 1){
                    left[ls] = equation[i];
                    ls++;
                  }

                  if(equation[i] == '('){
                    leftbracket = 1;
                  }

                 }
              }
              printf("Left half of equation %s\n", left);
              
              
              for(int i = 0 ; i < strlen(equation)-1;i++){
                 if(i > found){
                  right[rs] = equation[i];
                  rs++;
                 }
              }
              printf("Right half of equation %s\n", right);


              int type = 0; //0 is Alpha, 1 is Beta

              if((equation[found] == 'v' && equation[0] != '-') || (equation[found] == '^' && equation[0] == '-') || (equation[found] == '>' && equation[0] != '-') ){
                type = 1;
              }

              if(type == 0){
                // //check if it is a child first
                // if(isAChild(t,body) > 0){
                //   printf("We are a CHILD\n");
                //   struct tableau *otherchild = (t,current);
                //   addToEnd(otherchild,left);
                //   addToEnd(otherchild,right);
                // }
                // else{
                  addToEnd(body,left);
                  addToEnd(body,right);
                // }
                
              }

              if(type == 1){
                //If true we have a branch already, this means we have to add to those branches
                printf("RESULT OF HAS LEFT CHILD %d\n",hasLeftChild(body,current));
                printf("This is body %s and curretn %s\n",body->S->item, current->item);
                printf("This is the tab value, %s\n", t->S->item );
                readTab(t);


                if(hasLeftChild(body,current) == 1){
                  struct tableau *leftBranch = getLeftChild(t,current);
                  startNewBranch(leftBranch,left);
                  startNewBranch(leftBranch,right);
                  struct tableau *rightBranch = getRightChild(t,current);
                  startNewBranch(rightBranch,left);
                  startNewBranch(rightBranch,right);
                }
                else{
                  struct tableau *leftBranch = getLeftChild(t,current);
                  addToEnd(leftBranch,left);
                  struct tableau *rightBranch = getRightChild(t,current);
                  addToEnd(rightBranch,right);
                }

                readTab(t);

              }
            }
          }

          current = current->tail;
        }

        body = body->rest;

   }

  readTab(t);

}


int closed(struct tableau *t) {
  return(2);}
/*You should not need to alter the program below.*/
int main()

{ /*input a string and check if its a propositional formula */


  char *name = malloc(Fsize);

  FILE *fp, *fpout;

 
  /* reads from input.txt, writes to output.txt*/
  if ((  fp=fopen("input.txt","r"))==NULL){printf("Error opening file");exit(1);}
  if ((  fpout=fopen("output.txt","w"))==NULL){printf("Error opening file");exit(1);}

  int j;
  for(j=0;j<cases;j++)
    {
      fscanf(fp, "%s",name);/*read formula*/
      switch (parse(name))
	{case(0): fprintf(fpout, "%s is not a formula.  ", name);break;
	case(1): fprintf(fpout, "%s is a proposition.  ", name);break;
	case(2): fprintf(fpout, "%s is a negation.  ", name);break;
	case(3):fprintf(fpout, "%s is a binary.  ", name);break;
	default:fprintf(fpout, "What the f***!  ");
	}
      struct set S={name, NULL};
      struct tableau t={&S, NULL};
      if (parse(name)!=0){complete(&t);
	  if (closed(&t))  fprintf(fpout, "%s is not satisfiable.\n", name);
	  else fprintf(fpout, "%s is satisfiable.\n", name);
	}
      else  fprintf(fpout, "I told you, %s is not a formula.\n", name);
    }

 
  fclose(fp);
  fclose(fpout);
  free(name);

  return(0);
}





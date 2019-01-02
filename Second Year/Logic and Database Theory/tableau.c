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

void complete(struct tableau *t){
  
  char equation[100] = "";
  char h[100] = "";
  char temp[100] = "";
  int j = 0;

  equation[0] = '-';

  for(int i = 1; i < strlen(t->S->item)+1;i++){
    equation[i] = t->S->item[i-1];
  }

  //printf("%s\n",equation);

  //Getting ride of the - in front
  if(equation[1] == '-'){
    int incr = 0;

    while(equation[incr] == '-'){
      incr ++;
    }

    if(incr/2 == 0){
      int ab = 0;

      for(int i = incr; i < strlen(equation);i++){
        temp[ab] = equation[i];
        ab++;
      }
      printf("Even temp %s\n",temp);
      //t->S->tail = &temp;
    }
    else{
      int ab = 0;

      for(int i = incr-1; i < strlen(equation);i++){
        temp[ab] = equation[i];
        ab++;
      }
      //t->S->tail = &temp;
    }
    //printf("%s\n",t->S->tail);
  }

  //Loop here to call finder on all branches of the tableau
  int found = finder(t);

  //This means that it is a literal, so should move to another branch if there is one
  if(found == -1){
    printf("Literal %s\n\n",equation);

  } // This means that it can be split further, so continue
  else{
   
    int ls = 0;
    int rs = 0;
    int neg = 0;
    int leftbracket = 0;

    char left[100] = "";
    char right[100] = "";
    char begin[100] = "";

    int type = 0; //0 is Alpha, 1 is Beta

    printf("Type of rule %c\n",equation[found+1]);
    if(equation[found+1] == 'v'){
      type = 1;
    }





    printf("Full equation %s\n", equation);

    while(equation[neg] != '('){
      begin[neg] = equation[neg];
      neg ++;
    }

    strcpy(left,begin);
    strcpy(right,begin);
    ls += neg;
    rs += neg;

    for(int i = 0 ; i < strlen(equation);i++){  

       if(i <= found){

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
       if(i > found+1){
        right[rs] = equation[i];
        rs++;
       }
    }
    printf("Right half of equation %s\n\n", right);

  }

}

int finder(struct tableau *t){

    int found = -1;

    char equation[100] = "";

    strcpy(equation,t->S->item);

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





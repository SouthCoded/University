#include <stdio.h> 
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */

int Fsize=50;
int inputs=6;

int i;
int j;


/*put all your functions here.  You will need
1.
int parse(char *g) which returns 1 if a proposition, 2 if neg, 3 if binary, ow 0
Of course you will almost certainly need other functions.

Your program should read 6 formulas in a file called "input.txt" and output in the way indicated below to a file called "output.txt".
*/


char valid(char *g){

  char h[100] = "";
  int j = 0;

  printf("Valid %s\n",g);


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

  printf("Without %s\n",h);

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

int formula(char *g){

  int left_para = 0;
  int right_para = 0;
  char equation[strlen(g)];
  char h[100] = "";
  int j = 0;

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
    printf("%s\n",equation);
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

int main()
{ 
/*input 6 strings from "input.txt" */
  char *names[inputs];/*to store each of the input strings*/

  for (i=0;i<inputs;i++) names[i]=malloc(Fsize);/*create enough space*/

  FILE *fp, *fpout, *fopen();

  if ((  fp=fopen("input.txt","r"))==NULL){printf("Error opening file");exit(1);}
  if ((  fpout=fopen("output.txt","w"))==NULL){printf("Error opening file");exit(1);}/*ouputs to be sent to "output.txt"*/

  fscanf(fp,"%s %s %s %s %s %s",names[0],names[1], names[2], names[3],names[4],names[5]);/*read input strings from "input.txt"*/
 
  /*lets check your parser*/
  for(i=0;i<inputs;i++)
    {j=parse(names[i]);
      switch(j)
	{
	case(0):fprintf(fpout,"%s is not a formula\n", names[i]);break;
	case(1):fprintf(fpout,"%s is a proposition\n",names[i]);break;
	case(2):fprintf(fpout,"%s is a negation\n",names[i]);break;
	case(3):fprintf(fpout,"%s is a binary formula\n",names[i]);break;
	default:fprintf(fpout,"%s is not a formula\n",names[i]);break;
	}
    }
 
 
  fclose(fp);
  fclose(fpout);
 
  return(0);
}

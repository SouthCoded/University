#include <stdio.h>

char* stringCopy(char *s){

	char *copy = malloc(sizeof(char)*strlen(s)+1);
	char *cp = copy;

	while(*cp++ = *s++);
	*cp = '\0';
	return copy;


}

int main(){

	char s[5] = "Hello";
	stringCopy(s);

}


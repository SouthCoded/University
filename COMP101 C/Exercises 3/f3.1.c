#include <stdio.h>
#include <math.h>

int perimeter(int a, int b, int c){
	return a+b+c;
}

double semiperimeter(int a, int b, int c){
	double x = perimeter(a,b,c);
	return x/2;
}

double area(int a ,int b, int c){
	double x = semiperimeter(a,b,c);
	double y = x*(x-a)*(x-b)*(x-c);
	return sqrt(y);
}

int main(){

	int a,b,c;

	printf("Enter 3 values \n");
	scanf("%d %d %d",&a,&b,&c);

	printf("The values are a:%d b:%d c:%d \n",a,b,c);

	printf("%f \n",area(a,b,c));


}




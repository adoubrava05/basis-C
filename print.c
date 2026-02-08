#include <stdio.h>



int fact(int a){
	int b = a;
	while(a != 1){
		a--;
		b = a * b;
	}
	return b;
}



int main(){
	printf("Hello World");
	int c = fact(5);
	printf("\nThe Fact of 5 is: %d",c);
    int d = fact(10);
    printf("\nThe Fact of 10 is %d",d);
    int diff = d/c;
    printf("\nThe Fact of 10 is %d times larger then the Fact of 5", diff);
	return 0;
}

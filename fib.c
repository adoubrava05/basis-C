#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

typedef struct fibNum{
    mpz_t prev2;
    mpz_t prev1;
} fibNum;




void createNum(fibNum** num, int i){
    mpz_t newNum;
    mpz_inits(newNum, NULL);
    mpz_add(newNum, (*num)->prev1, (*num)->prev2);

    mpz_set((*num)->prev2, (*num)->prev1);
    mpz_set((*num)->prev1, newNum);


    //gmp_printf("\nF%d:   %Zd",i, newNum);
    mpz_clear(newNum);
}

int main(){
    fibNum* num = malloc(sizeof(fibNum));
    if(num == NULL){printf("MALLOC ERROR RETURNING");return 0;}
    mpz_inits(num->prev1, num->prev2, NULL);

    mpz_set_ui(num->prev1, 1);
    mpz_set_ui(num->prev2, 0);

    gmp_printf("\nF0:    %Zd", num->prev2);
    gmp_printf("\nF1:    %Zd", num->prev1);
   
    for(int i = 0; i < 30000; i++){
        createNum(&num, i+2);
    }
    gmp_printf("\n%Zd", num->prev1);
    return 0;
}

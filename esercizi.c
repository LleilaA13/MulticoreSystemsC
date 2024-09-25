#include <stdio.h>
//#include <mpi.h>

//exercise 1
/*Scriva un programma che legge in input due int.
1) il programma deve stampare se il primo numero e' maggiore, minore o uguale al secondo.
2) il programma deve stampare la somma e il prodotto dei due numeri
*/
int main(){
    int a = 0;
    int b = 0;
    // ora ci occupiamo di scan e print:
    printf("Inserire primo numero:\n"); 
    // Use scanf to read the first number and store it in variable 'a'
    scanf("%d", &a); // %d expects an integer input
    printf("Inserire secondo numero:\n");
    // Use scanf to read the second number and store it in variable 'b'
    scanf("%d", &b);

    int somma = a + b;
    int prodotto = a * b;

    if(a > b){
        printf("Il primo numero e maggiore del secondo");
    }
    else if(a < b){
        printf("Il primo numero e minore del secondo");
    }
    else{
        printf("i numeri sono uguali");
    }

    printf("\nSomma: %d, prodotto: %d \n", somma, prodotto);

    return 0;

}
#include <stdio.h> 
//Esempio array in C:
/*
int main(){
    
    int dim = 100;
    int array[dim];

    int i = 0;

    for(i = 0; i < dim; i++){
        array[i] = i;
    }

    for(i = 0; i < dim; i++){
        printf("%d \n", array[i]);
    }

    return 0;

}
*/


//esercizio 4:
/* Scriva un programma che legge in input 5 numeri interi e li salva in un array:
    1) Il programma stampa il numero più grande e il numero più piccolo.
    2) Il programma stampa la somma di tutti i numeri.

        N.B.: per svolgere l'esercizio si deve utilizzare un array
            e cicli FOR
*/

int main(){
    int array[5];
    int i = 0;

    for(i = 0; i < 5; i++){
        printf("Inserire numero: %d \n", i);
        scanf("%d", &array[i]);
    }

    int min = array[0];
    int max = array[0];
    int sum = 0;

    for(i = 0; i < 5; i++){
        if(array[i] < min)
            min = array[i];
        if(array[i] > max)
            max = array[i];
        
        sum += array[i];
    }

    printf("minimo: %d -  massimo: %d - somma: %d  \n", min, max ,sum);
    
    return 0;

}

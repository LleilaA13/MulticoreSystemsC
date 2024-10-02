//esercizio 8:
/*  Scrivere una funzione che data un'array di interi e un valore x cerca
il valore x nell'array. Se il valore x è presente allora restituirà la posizione
altrimenti un codice di errore 404.
*/

#include <stdio.h>

int ricerca(int* array, int dim, int x){
    for(int i = 0; i < dim; i++ ){
        if(x == array[i]){
            return i;
        }
    }
    return 404;
}

int main(){
    int array[10];
    for(int i = 0; i < 10; i++){
        array[i] = i;
    }
    int valore = ricerca(array, 10, 4);

    printf("\n il valore restituito dalla fct ricerca è: %d", valore);
}
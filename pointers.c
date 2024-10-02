// un puntatore e' una variable che contiene l'indirizzo di memoria di un'altra variabile.
    /* Per dichiarare un puntatore e'opportuna anteporre al nome della variabile un asterisco (*).
    - Esempio: dichiaro un puntatore a int e un puntatore a char:
                int *pa;
                char *pc;
        -> Quindi pa e' un puntatore che puo' contenere l'indirizzo in memoria
        di qualsiasi variabile INTERA.
        -> Invece pc puo' contenere l'indirizzo in memoria di qualsiasi variabile
        di tipo CHAR.


    variabile intera:
    int a = 3;         
    puntatore a intero:
    int *p;

    --> * operatore che restituisce il contenuto dell'oggetto puntato.
    --> & operatore che restituisce l'indirizzo in memoria della variabile.
*/

//Aritmetica dei puntatori:

/* 
    int a[10], x;
    int *p;
    p = &a[0]; -> Viene assegnato al puntatore p l'indirizzo in memoria del primo elemento dell'array a.
    x = *p; -> Viene assegnato alla var x, il valore contenuto nella locazione
            di memoria puntata da p
    p++; ----> Viene incrementato l'indirizzo in cui punta p.
    
*/
//esercizio 6:
/* Si scriva un programma che dichiara un array di char di 10 caratteri
e permetta all'utente di inserire in iunput una stringa che verra' salvata
nell'array.
    -Il programma deve dichiarare un puntatore di tipo char che punta all'array.
    -Successivamente, attraverso il puntatore, deve sostituire ogni elemento dell'array
    che e' un ciffra con il carattere *.
    -Infine stampare l'array di char.


#include <stdio.h>
int main(){
    
    char stringa[10];
    char *c;
    c = &stringa[0];    

    printf("Stringa in input: ");
    scanf("%s", stringa);

    while(*c != '\0'){
        if((*c >= '0' && *c <= '9')){
            *c = '*';
        }

        c++;
    }    
    printf("\n Stringa modificata: %s \n", stringa);
    return 0;

}
*/

//esercizio 7:
/* Si scriva un programma che dichiara due array di interi di 5 elementi 
e permette all'utente di riempirli.
    - Successivamente, tramite l'utilizzo di due puntatori, inverte il primo
    elemento di array1 con l'ultimo di array2, il secondo elemento di array1 con il penultimo
    di array2 e cosi via...
    - Infine stampa i due array modificati
*/

#include <stdio.h>

int main(){
    int array1[5];
    int array2[5];

    int *p1;
    int *p2;

    p1 = &array1[0];
    p2 = &array2[4];

    int i = 0;
    for(i = 0; i < 5; i++){ 
        
        /*The function scanf needs to modify the variable you're reading data into. 
        Since C passes arguments by value, the function wouldn't be able 
        to modify the original variable unless it receives a pointer to that variable.

    When you call scanf("%d", &array1[i]);, you are passing the address of array1[i] (using &), 
    so scanf can store the value entered by the user directly into that memory location.
    Without &, scanf would only receive the value stored in the variable, but it wouldn't know where to store the input. */

        printf("Input array1[%d]: ", i);
        scanf("%d", &array1[i]);    //This reads an integer input from the user and stores it in the i-th position of array1. 
                                    //The & is used because scanf requires the address of the variable to store the input.
        printf("\n Input array2[%d]: ", i);
        scanf("%d", &array2[i]);
    }
    
    for(i = 0; i < 5; i++){
        int a = *p1;
        *p1 = *p2;
        *p2 = a;
        p1++;
        p2--;
    }

    printf("\n Stampo gli array...\n");
    for(i = 0; i < 5; i++){
        printf("ARRAY1 array1[%d]: %d \n", i, array1[i]);
        printf("ARRAY2 array2[%d]: %d \n", i, array2[i]);
    }

    return 0;

}
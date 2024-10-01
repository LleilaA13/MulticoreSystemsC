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
*/

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
//Una stringa viene rappresentata come sequenza di caratteri che termina con '\0' (carattere terminatore)

//esercizio 5:
/* Si scriva un programma che legge in input una stringa e la salva in un array di char di 20 elementi.
Il programma deve sostituire tute le cifre che compaiono nella stringa con il carattere *
Infine deve stampare la stringa modificata
*/

#include <stdio.h>

int main(){
    char array[20];
    printf("stringa in input: \n");
    scanf("%s", array);

    int i = 0;
    while (array[i] != '\0')
    {
        if((array[i] >= '0' && array[i] <= '9')){
            array[i] = '*';
        }
        i++; 
    }

    printf("nuova stringa: %s \n", array); 
    
    return 0;

}

//La libreria string.h
// #include <string.h>
/* Alcune funzioni:
    - strLen(stringa);
    - strcpy(destinazione, sorgente);
    - strcat(destinazione, sorgente);
    - strcmp(s1, s2);

*/
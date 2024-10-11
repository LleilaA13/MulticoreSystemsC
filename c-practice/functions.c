/* Ogni funzione e' un piccolo programma indipendente dalle altre funzioni.
All'interno di una funzione possono essere definite delle variabili locali: le altre funzioni non le vedono.
Vengono create ogni volta che si entra nella funzione e distrutte (perdendo il valore) quando si esce.

    tipo nomeFunzione(parametri){
        definizioni_variabili_locali

        istruzioni
        eventuale return
    }

*/

//esempio:

#include <stdio.h>

int eleva(int b, int e){
    int k = 1;
    while(e-- > 0)
        k *= b;
    return k;
}

int main(){

    int x = 0, y = 0, z = 0;
    printf("Introduci numero: ");
    scanf("%d", &x);

    printf("Introduci potenza: ");
    scanf("%d", &y);

    z = eleva(x, y);
    printf("%d^%d = %d \n", x, y, z);

    return 0;
}

/* Passaggio di parametri:
        - I parametri vengono passati per valore alle funzioni.
    -> Questo significa che nella funzione viene creata una copia, quindi se il parametro viene cambiato durante l'esecuzione della funzione, 
    questo non ha effetto al di fuori della funzione stessa.
        - I parametri di tipo array sono invece passati per riferimento. 
    -> Questo significa che se i valori delle componenti dell'array sono alteratidurante l'esecuzione della funzione, 
    gli stessi valori sono alterati nell'array che viene passato come argomento durante la chiamata.
        - Come modificare i valori di variabili utilizzando delle funzioni?
    -> Dato che le funzioni ammettono la possibilità di restituire un solo valore, come possiamo fare se abbiamo bisogno di restituire più
    valori?
*/
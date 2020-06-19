#include "menu.h"

char MenuB(void){
    char op;
    printf ("Árvores Balanceadas : Menu\n");
    printf ("   1. Inserir novo elemento na árvore 2-3-4\n");
    printf ("   2. Remover elemento da árvore 2-3-4\n");
    printf ("   3. Imprimir árvore 2-3-4\n");
    printf ("   4. Converter em uma árvore rubro-negra\n");
    printf ("   5. Sair\n");
    scanf (" %c", &op);
    return op;
}

char MenuP(void){
    char op;
    printf ("Árvores Balanceadas : Menu\n");
    printf ("   1. Inserir novo elemento na árvore rubro-negra\n");
    printf ("   2. Remover elemento da árvore rubro-negra\n");
    printf ("   3. Imprimir árvore rubro-negra\n");
    printf ("   4. Sair\n");
    scanf (" %c", &op);
    return op;
}
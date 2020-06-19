
/* 
 * File:   Arvore.c
 * 
 * Author: Carlos Henrique Reis
 *
 * C source file que contêm as funções básicas e suas auxiliares da arvore
 * 
 * Created on 1 de Junho de 2015, 08:42
 */

#include "Arvore.h"
#include "VP.h"

no_t *cria_arvore (void){
    no_t *sentinela;
    sentinela = (no_t*) malloc (sizeof(no_t));
    if (!sentinela)
        return NULL;
    sentinela->dado = -10000;
    sentinela->cor = 'P';
    sentinela->f_dir = NULL;
    sentinela->f_esq = NULL;
    sentinela->pai = NULL;
    return sentinela;
}

no_t *cria_no (int dado){
    no_t *no;
    no = (no_t*) malloc (sizeof(no_t));
    if (!no)
        return NULL;
    no->dado = dado;
    no->cor = 'V';
    no->f_dir = NULL;
    no->f_esq = NULL;
    no->pai = NULL;
    return no;
}

void insere_no (no_t *sentinela, int dado){
    no_t *no, *aux, *auxpai;
    no = cria_no(dado);//Aloca memória para o nó
    if (!no){//Caso de falha na alocação de memória
        printf ("Erro de memória\n");
        return;
    }
    if (!sentinela->f_dir){//A árvore está vazia
        sentinela->f_dir = no;
        no->pai = sentinela;
        RestauraVPinsert(sentinela, no);
        return;
    }
    aux = sentinela->f_dir;//aux é responsavel por percorrer a arvore
    while (aux){//A árvore contêm dados
        auxpai = aux;
        if(dado<=aux->dado)//O no vai ser inserido a esquerda
            aux = aux->f_esq;
        else//O no vai ser inserido a direita
            aux = aux->f_dir;
    }//Encontrou o local correto de inserção do no
    if (dado<=auxpai->dado)//O no vai ser inserido a esquerda
        auxpai->f_esq = no;
    else//O no vai ser inserido a direita
        auxpai->f_dir = no;
    no->pai = auxpai;
    RestauraVPinsert(sentinela, no);
    return;
}

void percorreOrdem (no_t *arvore){
    if (!arvore)//Critéro de parada da função já que ela é recursiva
        return;
    percorreOrdem(arvore->f_esq);
    printf("%d->%c \n", arvore->dado,arvore->cor);
    percorreOrdem(arvore->f_dir);
}

no_t *busca_dado (no_t *sentinela, int dado){
    no_t *aux;//Variávle auxiliar responsavel por percorrer a árvore
    aux = sentinela->f_dir;
    if (!aux)//A árvore não contêm o dado pois ela está vazia
        return NULL;//return NULL pois nenhum nó contêm o dado buscado
    while ((aux) && (aux->dado !=dado)){//Percorre a árvore para buscar a posição do dado
        if (dado<=aux->dado)// O dado pode só pode estar a esquerda deste nó
            aux = aux->f_esq;
        else// O dado pode só pode estar a direita deste nó
            aux = aux->f_dir;
    }//O nó foi encontrado ou a árvore não contêm o dado buscado
    return aux;
}

void *Removefolha(no_t *no){//Trata a remoção do nó que é folha
    no_t *pai;//Variável auxiliar para fazer os devidos apontamentos
    pai = no->pai;
    if (no->dado >= pai->dado)
        pai->f_dir = NULL;
    else
        pai->f_esq = NULL;
    free (no);
    return;
}

no_t *Removeumfilho(no_t *no){
    no_t *x;//x é o filho que ficou no lugar y
    if (!no->f_esq){//filho esta a direita
        no->f_dir->pai = no->pai;
        if (no->dado<no->pai->dado)
            x = no->pai->f_esq = no->f_dir;
        else
            x = no->pai->f_dir = no->f_dir;
    }
    else{
        no->f_esq->pai = no->pai;
        if (no->dado<no->pai->dado)
            x = no->pai->f_esq = no->f_esq;
        else
            x = no->pai->f_dir = no->f_esq;
    }
    free (no);
    return x;
}

no_t *sucessor(no_t *no){
    no_t *aux;
    aux= no->f_dir;
    while (aux->f_esq)
        aux = aux->f_esq;
    return aux;
}

void remove_no (no_t *sentinela, int dado){
    int valor;// Armazena o valor do nó a ser de fato removido, y
    no_t *pai ,*y, *x, *z;
    char corY;//Variavel responsavel para  armazenar a cor de Y
    z = busca_dado (sentinela, dado);//Busca o dado na árvore
    if (!z){//A árvore está vazia, ou o no não está contido na árvore
        printf ("Árvore vazia, ou o dado não foi encontrado\n");
        return;
    }//senão o dado está na árvore
    //Encontrar y
    if ((z->f_esq) && (z->f_dir))//z possui dois filhos (y == sucessor(z))
        y = sucessor(z);
    else//z é folha ou possui um filho(y == z)
        y = z;
    z->dado = y->dado;
    corY = y->cor;//Devo saber qual é a cor de y
    valor = y->dado;//precisarei deste alor na chamada na funçao de restaurar as propriedades da árvore
    pai = y->pai;
    if ((!y->f_esq) && (!y->f_dir)){//x que é o filho será nulo
        x = NULL;
        Removefolha(y);
    }
    
    else//O y que é  nó a ser removido possui 1 filho
        x = Removeumfilho (y);
    //o Y foi removido
    if (corY == 'P')//caso o nó removido seja preto a arvore pode ter perdido sua caracteistica de redblck
       RestauraVPremove (sentinela->f_dir, pai, x, valor);
    return;//O nó foi removido com sucesso e a arvore foi atualizado
}
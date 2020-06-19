#include "Btree.h"

noB_t *cria_arvoreB (void){
    noB_t *raiz;
    raiz = NULL;
    return raiz;
}

int busca_binaria(noB_t *no, int dado) { 
  int meio, i, f; 
  i = 0;
  f = no->n_chaves;
  while (i <= f){
        meio = (i + f)/2;
        if (no->chaves[meio] == dado)
            return meio; //Encontrou. Retorna a posíção em que a chave está.
        else{ 
            if (no->chaves[meio] > dado)
                f = meio-1;
            else 
                i = meio+1;
        }
  }
  return i; //Não encontrou. Retorna a posição do ponteiro para o filho.
}

noB_t *busca(noB_t *raiz, int dado){
    noB_t *aux;
    int pos; //posição retornada pelo busca binária.
    aux = raiz;
    while (!aux){
        pos = busca_binaria(aux, dado);
        if (pos < aux->n_chaves && aux->chaves[pos] == dado)
            return aux;
        else 
            aux = aux->filhos[pos];
    }
    return NULL;
}



void insere_chave(noB_t *raiz, int dado, noB_t *f_dir){
    int k, pos;
    //busca para obter a posição ideal para inserir a nova chave
    pos = busca_binaria(raiz, dado);
    k = raiz->n_chaves;
    //realiza o remanejamento para manter as chaves ordenadas
    while (k > pos && dado < raiz->chaves[k-1]){
        raiz->chaves[k] = raiz->chaves[k-1];
        raiz->filhos[k+1] = raiz->filhos[k];
        k--;
    }
    //insere a chave na posição ideal
    raiz->chaves[pos] = dado;
    raiz->filhos[pos+1] = f_dir;
    raiz->n_chaves++;
}

noB_t *insere(noB_t *raiz, int dado, int *alt_h, int *dado_return){
    int i, j, pos, chave_meio; //chave_meio é uma variável auxiliar que ajuda a subir a chave do meio para o pai, caso a página esteha cheia
    noB_t *temp, *filho_dir; //ponteiro para o filho à direita da chave 

    if (raiz == NULL){//O nó anterior é o ideal para inserir a nova chave (chegou em um nó folha)
        *alt_h = V;
        *dado_return = dado;
        return(NULL);
    }
    else {
        pos = busca_binaria(raiz,dado);
        if (raiz->n_chaves > pos && raiz->chaves[pos] == dado){
            printf("Chave já contida na Árvore");
            *alt_h = F;
        }
        else {//desce na árvore até encontrar o nó folha para inserir a chave.
            filho_dir = insere(raiz->filhos[pos],dado,alt_h,dado_return);
            if (*alt_h == V){ //Se true deve inserir a info_retorno no nó.
                if (raiz->n_chaves < ordem-1){ //Tem espaço na página
                    insere_chave(raiz, *dado_return, filho_dir);
                    *alt_h = F;
                }
                else { //Overflow. Precisa subdividir
                    temp = (noB_t*) malloc (sizeof(noB_t));
                    temp->n_chaves = 0;
                    //inicializa filhos com NULL
                    for (i = 0; i < ordem; i++)
                        temp->filhos[i] = NULL;
                    //elemento mediano que vai subir para o pai
                    chave_meio = raiz->chaves[ordem/2];
                    //insere metade do nó raiz no temp (efetua subdivisão)
                    temp->filhos[0] = raiz->filhos[(ordem/2)+1];
                    for (i = (ordem/2)+1; i < ordem-1; i++)
                        insere_chave(temp, raiz->chaves[i], raiz->filhos[i+1]);
                    //atualiza nó raiz. 
                    for (i = (ordem/2); i<(ordem-1); i++){
                        raiz->chaves[i] = 0;
                        raiz->filhos[i+1] = NULL;
                    }
                    raiz->n_chaves = (ordem/2);
                    //Verifica em qual nó será inserida a nova chave
                    if (pos <= (ordem/2)+1)
                        insere_chave(raiz, *dado_return, filho_dir);
                    else 
                        insere_chave(temp, *dado_return, filho_dir);
                    //retorna o mediano para inserí-lo no nó pai e o temp como filho direito do mediano.
                    *dado_return = chave_meio;
                    return(temp);
                }
            }
        }
    }
  }

noB_t *cria_noB (void){
    noB_t *no;
    no = (noB_t*) malloc (sizeof(noB_t));
    if (!no)
        return NULL;
    return no;
}

noB_t *inserir_dadoB(noB_t *raiz, int dado){
    int i, dado_return, alt_h;
    noB_t *f_dir, *raiz_n;
    f_dir = insere(raiz, dado, &alt_h, &dado_return);
    if(alt_h == V){
        raiz_n = cria_noB ();
        if (!raiz_n){
            printf ("Erro\n");
            return;
        }
        raiz_n->n_chaves = 1;
        raiz_n->chaves[0] = dado_return;
        raiz_n->filhos[0] = raiz;
        raiz_n->filhos[1] = f_dir;
        for (i = 2; i <= ordem; i++)
          raiz_n->filhos[i] = NULL;
        return raiz_n;
    }
    return raiz;
}

void em_ordem(noB_t *raiz){
    int i;
    if (!raiz)
        return;
    for (i = 0; i < raiz->n_chaves; i++){
        em_ordem(raiz->filhos[i]);
        printf("\n%d", raiz->chaves[i]);
    }
    em_ordem(raiz->filhos[i]);
}

/*int main (void){
    noB_t *raiz;
    raiz = cria_arvoreB();
    raiz = inserir_dadoB(raiz, 31);
    raiz = inserir_dadoB(raiz, 12);
    raiz = inserir_dadoB(raiz, 35);
    raiz = inserir_dadoB(raiz, 11);
    
    raiz = inserir_dadoB(raiz, 36);
    em_ordem(raiz);
    return 0;
}*/
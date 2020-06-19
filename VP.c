/* 
 * File:   VP.h
 * 
 * Author: Carlos Henrique Reis
 * 
 * C header file que contm os protótipos das funções de restauração das propriedades da arvore vermelha e preta
 *
 * Created on 1 de Junho de 2015, 16:22
 */


#include "VP.h"

void rotacaoEsq(no_t *x){
    no_t *y;
    y = x->f_dir;
    x->f_dir=y->f_esq;
    if(x->f_dir)
        x->f_dir->pai=x;
    y->f_esq=x;
    y->pai=x->pai;
    x->pai=y;
    if(y->pai->dado<y->dado)
        y->pai->f_dir=y;
    else
        y->pai->f_esq=y;
    return;
}

void rotacaoDir(no_t *x){
    no_t *y;
    y = x->f_esq;
    x->f_esq = y->f_dir;
    if(x->f_esq)
        x->f_esq->pai=x;
    y->f_dir=x;
    y->pai=x->pai;
    x->pai=y;
    if(y->pai->dado<y->dado)
        y->pai->f_dir=y;
    else
        y->pai->f_esq=y;
    return;
}

void RestauraVPinsert (no_t *A, no_t *no){
    no_t *Pai, *avo, *tio;
    Pai = no->pai;
    while (Pai->cor == 'V'){
        avo = Pai->pai;
        if(no->dado < avo->dado){//no ha esquerda
            tio = avo->f_dir;
            if((tio) && (tio->cor == 'V')){//Caso 1
                Pai->cor = 'P';
                tio->cor = 'P';
                avo->cor = 'V';
                no = avo;
                Pai = no->pai;
            }
            else{
                if (no == Pai->f_dir){//Pode colocar valores dos dados // Caso 2
                    rotacaoEsq(Pai);
                    no = Pai;
                    Pai = no->pai;
                }
                //Caso 3
                Pai->cor = 'P';
                avo->cor = 'V';
                rotacaoDir (avo);
                    
            }
        }           
        else{//no ha direita(Espelhar)
            tio = avo->f_esq;
            if((tio)&&(tio->cor == 'V')){//Caso 1
                Pai->cor = 'P';
                tio->cor = 'P';
                avo->cor = 'V';
                no = avo;
                Pai = no->pai;
            }
            else{
                if (no == Pai->f_esq){//Pode colocar valores dos dados // Caso 2
                    rotacaoDir(Pai);
                    no = Pai;
                    Pai = no->pai;
                }
                //Caso 3
                Pai->cor = 'P';
                avo->cor = 'V';
                rotacaoEsq (avo);
            }
        }
    }
    A->f_dir->cor = 'P';
    return;
}

void RestauraVPremove(no_t *A, no_t *pai, no_t *x, int valor){
    no_t *w;
    char corX;
    if (!x)//X é nulo logo ele é preto
        corX = 'P';
    else//x não é nulo logo ele pode ser vermelho ou ṕreto
        corX = x->cor;
    while ((x != A) && (corX == 'P')){
        if (valor<pai->dado){//x estará a esquerda de seu pai
            w = pai->f_dir;//w será o irmão de x
            if(w->cor == 'V'){//caso 1
                w->cor = 'P';
                pai->cor = 'V';
                rotacaoEsq(pai);
                w = pai->f_dir;
            }
            if (((!w->f_dir) || (w->f_dir->cor == 'P')) && ((!w->f_esq) ||(w->f_esq->cor == 'P'))){// Caso 2 - Neste caso o fihlo será preto caso a ele seja nulo ou ele exista e sua cor seja preta 
               w->cor = 'V';
               x = pai;//Atualizamos x - Fazemps isso pois o x pode ser nulo
               pai = x->pai;//atualiza o pai
               corX = x->cor;
            }
            else{
                if ((w->f_esq) && (w->f_esq->cor == 'P')){//caso 3 ->Testa se o filho esquerdo de w é vermelho
                    w->f_esq->cor = 'P';
                    w->cor = 'V';
                    rotacaoDir(w);
                    w = pai->f_dir;
                }
                //caso 4
                w->cor = pai->cor;
                pai->cor = 'P';
                w->f_dir->cor = 'P';
                rotacaoEsq(pai);
                x = A->f_dir;
                corX = x->cor;
            }
        }
        else{//x está a direita de seu pai
            w = pai->f_esq;//w será o irmão de x
            if(w->cor == 'V'){//caso 1
                w->cor = 'P';
                pai->cor = 'V';
                rotacaoDir(pai);
                w = pai->f_esq;
            }
            if (((!w->f_dir) || (w->f_dir->cor == 'P') ) && ((!w->f_esq) ||(w->f_esq->cor == 'P'))){// Caso 2 - Neste caso o fihlo será preto caso a ele seja nulo ou ele exista e sua cor seja preta 
               w->cor = 'V';
               x = pai;//Atualizamos x - Fazemps isso pois o x pode ser nulo
               pai = x->pai;//atualiza o pai
               corX = x->cor;
            }
            else{
                if ((w->f_dir) && (w->f_dir->cor == 'P')){//caso 3 ->Testa se o filho esquerdo de w é vermelho
                    w->f_dir->cor = 'P';
                    w->cor = 'V';
                    rotacaoEsq(w);
                    w = pai->f_esq;
                }
                //caso 4
                w->cor = pai->cor;
                pai->cor = 'P';
                w->f_esq->cor = 'P';
                rotacaoDir(pai);
                x = A;
                corX = x->cor;
            }
        }
    }
    if(x)//A arvore pode estar vazia, ou seja x pode ser nulo
        x->cor = 'P';
    return;
}
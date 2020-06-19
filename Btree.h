/* 
 * File:   Btree.h
 * Author: carlos
 *
 * Created on 15 de Junho de 2015, 17:03
 */

#include <stdio.h>
#include <stdlib.h>



#ifndef BTREE_H
#define	BTREE_H

#define ordem 4

#define V 1
#define F 0

struct nob{
    int n_chaves;//Nùmeros de chaves que contem no nó (Página)
    int chaves[ordem-1];//vetor que contem as chaves da árvore
    struct no *filhos[ordem];//Vetor de ponteiros   
};

typedef struct nob noB_t;


noB_t *cria_arvoreB (void);

int busca_binaria(noB_t *no, int dado);

noB_t *busca(noB_t *raiz, int dado);

void insere_chave(noB_t *raiz, int dado, noB_t *f_dir);

noB_t *insere(noB_t *raiz, int dado, int *alt_h, int *dado_return);

noB_t *cria_noB (void);

noB_t *inserir_dadoB(noB_t *raiz, int dado);

void em_ordem(noB_t *raiz);

#endif	/* BTREE_H */


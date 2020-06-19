/* 
 * File:   Arvore.h
 * 
 * Author: Carlos Henrique Reis
 *
 * C header file que contêm as funções básicas e suas auxiliares da arvore
 * 
 * Created on 1 de Junho de 2015, 08:42
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef ARVORE_H
#define	ARVORE_H

struct no {//Regitro responsavel pelos elementos do nó
    int dado;
    char cor;
    struct no *f_esq;
    struct no *f_dir;
    struct no *pai;
};

typedef struct no no_t;

no_t *cria_arvore (void);//Aloca mamória para sentinela e atribui os valores adequados para as variaveis - A função retorna um ponteiro sentinela

no_t *cria_no (int dado);//Aloca memória para um nó e atribui os valores adequados para as variáveos deste nó - A função retorna ponteiro nó

void insere_no (no_t *sentinela, int dado);//Insere um novo nó na árvore e no final restaura as propriedades da árvore(Uso da função balVP)

void percorreOrdem (no_t *arvore);//Percorre a árvore e imprime os valores contidos na arvore, ordenados com suas respectivas cores

no_t *busca_dado (no_t *sentinela, int dado);//Busca um dado na árvore e retorna um ponteiro que aponta para o nó que contêm  chave buscada, ou NULL caso o dado não esteja na árvore
        
void *Removefolha(no_t *no);//remove o no caso ele seja folha

no_t *Removeumfilho(no_t *no);//Remove o no que possui um filho e retorna o filho deste nó
              
//void *RemovedoisFilhos(no_t *no) ->Função não foi ultilizada na remoção da RedBlack

no_t *sucessor(no_t *z);//Encontra e retorna um ponteiro que aponta para o nó sucessor do nó z

#endif	/* ARVORE_H */


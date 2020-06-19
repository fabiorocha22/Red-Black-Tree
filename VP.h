/* 
 * File:   VP.h
 * 
 * Author: Carlos Henrique Reis
 * 
 * C header file que contm os protótipos das funções de restauração das propriedades da arvore vermelha e preta
 *
 * Created on 1 de Junho de 2015, 16:22
 */

#include "Arvore.h"

#ifndef VP_H
#define	VP_H

void rotacaoEsq(no_t *x);//Faz uma rotação para esquerda no nó X

void rotacaoDir(no_t *x);//Faz uma rotação para direita no nó X

void RestauraVPinsert(no_t *A, no_t *no);//Função que restura as propriedades da árvore rubru-negra quando um nó é inserido nela

void RestauraVPremove(no_t *A, no_t *pai, no_t *x, int valor);//Função que restura as propriedades da árvore rubru-negra quando um nó X é removido

#endif	/* VP_H */
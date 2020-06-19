#include "menu.h"
#include "Arvore.h"
#include "Btree.h"
#include "VP.h"

int main (void){
    FILE *arq;
    char nomeArquivo[30];
    no_t *sentinela;
    noB_t *raizB;
    int dado, i, num;
    char op_menuB, op_menuP, tipo, sair;
    //manipulação de arquivo
    raizB = cria_arvoreB();
    printf("Digite o nome do arquivo de entrada: \n");
    scanf(" %s", nomeArquivo);
    arq = fopen(nomeArquivo, "r");//Abre o arquivo
    if (arq == NULL){//testa e o arquivo existe
        printf("Erro ao abrir o arquivo %s", nomeArquivo);
        return 0;
    }
    while(!feof(arq)){//Leitura dos dados do arquivo
        fscanf(arq, "%d", &dado);
        if (ferror(arq)){
            printf("Erro ao ler arquivo de dados");
            return 0;
        }
       // raizB = inserir_dadoB(raizB, dado);
        tipo = 'B';
    }
    //Fim da manipulação do arquivo
    printf ("Arvore 2-3-4, após a leitura dos arquivos\n");
    //Imprime(raizB);//print da arvore- em ordem
    sair = 'N';
    while(sair == 'N'){
        if(tipo == 'B'){
            op_menuB = MenuB();//meNu da arvoer 234
            switch(op_menuB){
                case '1':
                    printf("Digite o dado a ser inserido:   ");
                    scanf(" %d", &dado);
                    //raizB = inserir_dadoB(raizB, dado);
                    break;
                case '2':
                    printf("Digite a chave que você deseja remover: \n");
                    scanf(" %d", &dado);
                    //raiz = remove_dadoB(raizB, dado);
                    break;
                case '3':
                    //Imprime(raizB);//print da arvore- em ordem
                    break;
                case'4':
                    sentinela = cria_arvore();
                    //sentinela = converte_VP(raiz);
                    tipo= 'P';
                    break;
                case '5':
                    sair = 'S';
                    break;
                default:
                    printf ("Opção inválida\n");
                    break;
            }
        }
        else{
            op_menuP = MenuP();//menu da arvoer 234
            switch(op_menuP){
                case '1':
                    printf("Digite o dado a ser inserido:   ");
                    scanf(" %d", &dado);
                    insere_no (sentinela, dado);
                    break;
                case '2':
                    printf("Digite a chave que você deseja remover: \n");
                    scanf(" %d", &dado);
                    remove_no (sentinela, dado);
                    break;
                case '3':
                    percorreOrdem(sentinela->f_dir);//print da arvore- em ordem
                    break;
                case'4':
                    sair = 'S';
                    break;
                default:
                    printf ("Opção inválida\n");
                    break;
            }
        }
    }
}
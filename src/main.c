#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "estado.h"
#include "funcsjogo.h"
#include "saveload.h"

int main() {
    ESTADO e = {0};
    ESTADOSH historico = malloc(sizeof(struct estadosh));
    historico = NULL;

    int quit = 0;
    int inGame = 0;
    char linha[50];
    char c1;
    int x, y, jp = 0, jogInv = 0;
    int* ajudaPos = malloc(sizeof(int));
    *ajudaPos = 0;
    POSICAO jogadasP[60];

    while(!quit) {
        jp = jogadasPossiveis(e,jogadasP);
        if(!inGame) printf("> ");
        else printf("%c> ",e.peca == VALOR_X ? 'X' : 'O');
        fgets(linha,50,stdin);
        switch(toupper(linha[0])) {
            case 'N':
                sscanf(linha + 1," %c",&c1);
                newBoard(&e,c1 == 'X' ? VALOR_X : VALOR_O,'0');
                inGame = 1;
                historico = NULL;
                break;
            case 'J':
                sscanf(linha + 1,"%d %d",&y,&x);
                jogInv = 1;
                ESTADOSH new = malloc(sizeof(struct estadosh));
                new->e = e;
                new->prox = historico;
                historico = new;
                for(int i = 0; i < jp; i++) {
                    if(jogadasP[i].lin == y && jogadasP[i].col == x) {
                        jogar(&e,y,x);
                        e.peca = e.peca == VALOR_O ? VALOR_X : VALOR_O;
                        jogInv = 0;
                    }
                }
                break;
            case 'S':
                *ajudaPos = 1;
                break;
            case 'E': {
                if(grava(e,strtok(linha + 2,"\n"),jp,jogadasP)) printf("\nErro ao guardar ficheiro.\n\n");
                else printf("\nFicheiro guardado com sucesso!\n\n");
                break; }
            case 'L':
                // if(lerDeFicheiro(&e)) {
                //     printf("Jogo carregado com sucesso!");
                //     inGame = 1;
                // }
                // else printf("Erro ao carregar jogo, ficheiro não encontrado.");
            case 'U':
                if(historico) {
                    e = historico->e;
                    ESTADOSH temp = historico;
                    historico = historico->prox;
                    free(temp);
                }
                else printf("\nImpossível anular jogada.\n\n");
                break;
            case 'Q':
                quit = 1;
                break;

        }
        if(inGame && !quit) {
            printa(e, ajudaPos, jp, jogadasP);
            printf("X: %2d       O: %2d\n\n",score(e,VALOR_X),score(e,VALOR_O));
            if(jogInv) printf("Jogada inválida! Tente novamente.\n\n");
        }
        jogInv = 0;
    }


    /* printf("\n%c, é a tua vez de jogar!\n", e.peca == VALOR_X ? 'X' : 'O');
    POSICAO pos[60];
    int jp = jogadasPossiveis(e,pos);
    printa(e,jp,pos);
    printf("\n"); */

    return 0;
}
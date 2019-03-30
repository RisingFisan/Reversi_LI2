#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "estado.h"
#include "funcsjogo.h"

int main() {
    ESTADO e = {0};

    int quit = 0;
    int inGame = 0;
    char linha[50];
    char c1;
    int x, y, jp = 0, jogInv = 0;
    int* ajudaPos = malloc(sizeof(int));
    *ajudaPos = 0;
    POSICAO jogadasP[60];

    while(!quit) {
        if(!inGame) printf("> ");
        else printf("%c> ",e.peca == VALOR_X ? 'X' : 'O');
        fgets(linha,50,stdin);
        switch(toupper(linha[0])) {
            case 'N':
                sscanf(linha + 1," %c",&c1);
                newBoard(&e,c1 == 'X' ? VALOR_X : VALOR_O,'M');
                inGame = 1;
                break;
            case 'J':
                sscanf(linha + 1,"%d %d",&y,&x);
                jp = jogadasPossiveis(e,jogadasP);
                jogInv = 1;
                for(int i = 0; i < jp; i++) {
                    if(jogadasP[i].lin == y && jogadasP[i].col == x) {
                        /*jogar(&e,y,x);*/
                        jogInv = 0;
                    }
                }
                break;
            case 'S':
                jp = jogadasPossiveis(e,jogadasP);
                *ajudaPos = 1;
                break;
            case 'Q':
                quit = 1;
                break;

        }
        if(inGame && !quit) {
            printa(e, ajudaPos, jp, jogadasP);
            printf("X: %2d       O: %2d\n",score(e,VALOR_X),score(e,VALOR_O));
            if(jogInv) printf("Jogada inválida! Tente novamente.\n");
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
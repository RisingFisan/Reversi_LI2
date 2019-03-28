#include <stdio.h>
#include "estado.h"
#include "funcsjogo.h"

int main()
{
    ESTADO e = {0};
    e.peca = VALOR_X;
    // for(int i = 0; i < 8; i++) {
    //     for(int j = 0; j < 8; j++) {
    //         e.grelha[i][j] = VAZIA;
    //     }
    // }
    // estado inicial do tabuleiro. Inicio do jogo!
    e.grelha[3][4] = VALOR_X;
    e.grelha[4][3] = VALOR_X;
    e.grelha[3][3] = VALOR_O;
    e.grelha[4][4] = VALOR_O;


    printf("\n%c, é a tua vez de jogar!\n", e.peca == VALOR_X ? 'X' : 'O');
    POSICAO pos[60];
    int jp = jogadasPossiveis(e,pos);
    printa(e,jp,pos);
    printf("Score\nX: %2d\nO: %2d",score(e,VALOR_X),score(e,VALOR_O));
    printf("\n");

    return 0;
}
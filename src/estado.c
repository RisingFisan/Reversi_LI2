//
// Created by pja on 28/02/2019.
//
#include <stdio.h>
#include "estado.h"


// exemplo de uma função para imprimir o estado (Tabuleiro)
void printa(ESTADO e, int nPos, POSICAO pos[]) {
    char c = ' ';

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch (e.grelha[i][j]) {
                case VALOR_O: {
                    c = 'O';
                    break;
                }
                case VALOR_X: {
                    c = 'X';
                    break;
                }
                case VAZIA: {
                    c = '-';
                    break;
                }
            }
            for(int k = 0; k < nPos; k++) {
                if(i == pos[k].lin && j == pos[k].col) {
                    c = '.';
                }
            }
            printf("%c ", c);

        }
        printf("\n");
    }

}


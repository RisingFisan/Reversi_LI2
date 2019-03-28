#include "estado.h"
#include "funcsjogo.h"
#include <stdio.h>

int score(ESTADO e, VALOR peca) {
    int n = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(e.grelha[i][j] == peca) n++;
        }
    }
    return n;
}

int jogadaH(ESTADO e, VALOR peca, POSICAO p);
int jogadaV(ESTADO e, VALOR peca, POSICAO p);
int jogadaD(ESTADO e, VALOR peca, POSICAO p);

int jogadasPossiveis(ESTADO e, POSICAO pos[]) {
    VALOR peca = e.peca;
    int n = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(e.grelha[i][j] != VAZIA) continue;
            else {
                POSICAO p = { .lin = i, .col = j};
                if(jogadaH(e, peca, p) || jogadaV(e, peca, p) || jogadaD(e, peca, p)) pos[n++] = p;
            }
        }
    }
    return n;
}

int jogadaH(ESTADO e, VALOR peca, POSICAO p) {
    VALOR pecaRival = peca == VALOR_X ? VALOR_O : VALOR_X;
    int pecasPraDestruir = 0;
    for(int i = p.col + 1; i < 8; i++) {
        if(e.grelha[p.lin][i] == VAZIA) break;
        else if(e.grelha[p.lin][i] == pecaRival) pecasPraDestruir++;
        else if(e.grelha[p.lin][i] == peca && pecasPraDestruir) return 1;
    }
    pecasPraDestruir = 0;
    for(int i = p.col - 1; i >= 0; i--) {
        if(e.grelha[p.lin][i] == VAZIA) break;
        else if(e.grelha[p.lin][i] == pecaRival) pecasPraDestruir++;
        else if(e.grelha[p.lin][i] == peca && pecasPraDestruir) return 1;
    }
    return 0;
}

int jogadaV(ESTADO e, VALOR peca, POSICAO p) {
    VALOR pecaRival = peca == VALOR_X ? VALOR_O : VALOR_X;
    int pecasPraDestruir = 0;
    for(int i = p.lin + 1; i < 8; i++) {
        if(e.grelha[i][p.col] == VAZIA) break;
        else if(e.grelha[i][p.col] == pecaRival) pecasPraDestruir++;
        else if(e.grelha[i][p.col] == peca && pecasPraDestruir) return 1;
    }
    pecasPraDestruir = 0;
    for(int i = p.lin - 1; i >= 0; i--) {
        if(e.grelha[i][p.col] == VAZIA) break;
        else if(e.grelha[i][p.col] == pecaRival) pecasPraDestruir++;
        else if(e.grelha[i][p.col] == peca && pecasPraDestruir) return 1;
    }
    return 0;
}

int jogadaD(ESTADO e, VALOR peca, POSICAO p) {
    VALOR pecaRival = peca == VALOR_X ? VALOR_O : VALOR_X;
    int pecasPraDestruir = 0;
    int i = p.lin + 1, j = p.col + 1;
    while(i < 8 && j < 8) {
        if(e.grelha[i][j] == VAZIA) break;
        else if(e.grelha[i][j] == pecaRival) pecasPraDestruir++;
        else if(e.grelha[i][j] == peca && pecasPraDestruir) return 1;
        i++;
        j++;
    }
    pecasPraDestruir = 0;
    i = p.lin - 1, j = p.col - 1;
    while(i >= 0 && j >= 0) {
        if(e.grelha[i][j] == VAZIA) break;
        else if(e.grelha[i][j] == pecaRival) pecasPraDestruir++;
        else if(e.grelha[i][j] == peca && pecasPraDestruir) return 1;
        i--;
        j--;
    }
    return 0;
}
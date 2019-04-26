#include "estado.h"
#include "funcsjogo.h"
#include <stdio.h>

/** score calcula a pontuação (nº de peças) de um jogador e devolve-a.
* @param e estado do jogo
* @param peca peça do jogador cuja pontuação se quer calcular
* @return a pontuação
*/

int score(ESTADO e, VALOR peca) {
    int n = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(e.grelha[i][j] == peca) n++;
        }
    }
    return n;
}

int jogadasPossiveis(ESTADO e, VALOR peca, POSICAO pos[]) {
    int n = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(e.grelha[i][j] != VAZIA) continue;
            else {
                POSICAO p = { .lin = i, .col = j, .dest = 0};
                if(jogadaH(e, peca, p) || jogadaV(e, peca, p) || jogadaD(e, peca, p)) pos[n++] = p;
            }
        }
    }
    return n;
}

int jogadaH(ESTADO e, VALOR peca, POSICAO p) {
    VALOR pecaRival = peca == VALOR_X ? VALOR_O : VALOR_X;
    int pecasPraDestruir = 0;
    int valida = 0;
    for(int i = p.col + 1; i < 8; i++) {
        if(e.grelha[p.lin][i] == VAZIA) break;
        else if(e.grelha[p.lin][i] == pecaRival) pecasPraDestruir++;
        else if(e.grelha[p.lin][i] == peca) {
            if(pecasPraDestruir) {
                p.dest += pecasPraDestruir;
                valida = 1;
            }
            else break;
        }
    }
    pecasPraDestruir = 0;
    for(int i = p.col - 1; i >= 0; i--) {
        if (e.grelha[p.lin][i] == VAZIA) break;
        else if (e.grelha[p.lin][i] == pecaRival) pecasPraDestruir++;
        else if (e.grelha[p.lin][i] == peca) {
            if (pecasPraDestruir) {
                p.dest += pecasPraDestruir;
                valida = 1;
            }
            else break;
        }
    }
    return valida;
}

int jogadaV(ESTADO e, VALOR peca, POSICAO p) {
    VALOR pecaRival = peca == VALOR_X ? VALOR_O : VALOR_X;
    int pecasPraDestruir = 0;
    int valida = 0;
    for(int i = p.lin + 1; i < 8; i++) {
        if(e.grelha[i][p.col] == VAZIA) break;
        else if(e.grelha[i][p.col] == pecaRival) pecasPraDestruir++;
        else if(e.grelha[i][p.col] == peca) {
            if(pecasPraDestruir) {
                p.dest += pecasPraDestruir;
                valida = 1;
            }
            else break;
        }    
    }
    pecasPraDestruir = 0;
    for(int i = p.lin - 1; i >= 0; i--) {
        if(e.grelha[i][p.col] == VAZIA) break;
        else if(e.grelha[i][p.col] == pecaRival) pecasPraDestruir++;
        else if(e.grelha[i][p.col] == peca) {
            if(pecasPraDestruir) {
                p.dest += pecasPraDestruir;
                valida = 1;
            }
            else break;
        }  
    }
    return valida;
}

int jogadaD(ESTADO e, VALOR peca, POSICAO p) {
    VALOR pecaRival = peca == VALOR_X ? VALOR_O : VALOR_X;
    int pecasPraDestruir = 0;
    int valida = 0;
    int i = p.lin + 1, j = p.col + 1;
    while(i < 8 && j < 8) {
        if(e.grelha[i][j] == VAZIA) break;
        else if(e.grelha[i][j] == pecaRival) pecasPraDestruir++;
        else if(e.grelha[i][j] == peca) {
            if(pecasPraDestruir) {
                p.dest += pecasPraDestruir;
                valida = 1;
            }
            else break;
        }
        i++;
        j++;
    }
    pecasPraDestruir = 0;
    i = p.lin - 1, j = p.col - 1;
    while(i >= 0 && j >= 0) {
        if(e.grelha[i][j] == VAZIA) break;
        else if(e.grelha[i][j] == pecaRival) pecasPraDestruir++;
        else if(e.grelha[i][j] == peca) {
            if(pecasPraDestruir) {
                p.dest += pecasPraDestruir;
                valida = 1;
            }
            else break;
        }
        i--;
        j--;
    }
    pecasPraDestruir = 0;
    i = p.lin + 1, j = p.col - 1;
    while(i < 8 && j >= 0) {
        if(e.grelha[i][j] == VAZIA) break;
        else if(e.grelha[i][j] == pecaRival) pecasPraDestruir++;
        else if(e.grelha[i][j] == peca) {
            if(pecasPraDestruir) {
                p.dest += pecasPraDestruir;
                valida = 1;
            }
            else break;
        }
        i++;
        j--;
    }
    pecasPraDestruir = 0;
    i = p.lin - 1, j = p.col + 1;
    while(i >= 0 && j < 8) {
        if(e.grelha[i][j] == VAZIA) break;
        else if(e.grelha[i][j] == pecaRival) pecasPraDestruir++;
        else if(e.grelha[i][j] == peca) {
            if(pecasPraDestruir) {
                p.dest += pecasPraDestruir;
                valida = 1;
            }
            else break;
        }
        i--;
        j++;
    }
    return valida;
}

void altera (ESTADO* e, POSICAO peca, POSICAO p1) {
    int j = 0;
    int i = 0;
    VALOR PECA = e->peca;
    if (peca.lin == p1.lin) {
        if (peca.col > p1.col) {
            for (i = p1.col+1; i < peca.col; i++) e->grelha[peca.lin][i] = PECA;
        }
        else {
            for (i = peca.col+1; i < p1.col; i++) e->grelha[peca.lin][i] = PECA;
        }
    }
    if (peca.col == p1.col) {
        if (peca.lin > p1.lin) {
            for (i = p1.lin+1; i < peca.lin; i++) e->grelha[i][peca.col] = PECA;
        }
        else {
            for (i = peca.lin+1; i < p1.lin; i++) e->grelha[i][peca.col] = PECA;
        }
    }
    if (peca.lin != p1.lin && peca.col != p1.col && peca.lin == peca.col && p1.lin == p1.col) {
        if (peca.lin > p1.lin) {
            for (i = p1.lin+1; i<peca.lin; i++) e->grelha[i][i] = PECA;
        }
        else {
            for (i = peca.lin+1; i<p1.lin; i++) e->grelha[i][i] = PECA;
        }
    }
    if (peca.lin != p1.lin && peca.col != p1.col) {
        if (peca.lin > p1.lin) {
            j = p1.col-1;
            for (int i = p1.lin+1; i<peca.lin && j>peca.col ; i++) { 
                e->grelha[i][j] = PECA; 
                j--;
            }
        }
        else {
            j = peca.col-1;
            for (int i = peca.lin+1; i<p1.lin && j>p1.col; i++) {
                e->grelha[i][j] = PECA;
                j--;
            }
        }   
    }
}

void jogar (ESTADO* e, int l, int c) {
    POSICAO p1, p = {l,c};
    e->grelha[l][c] = e->peca;
    VALOR PECA = e->peca;
    int i, j;
    for (i = c - 1; i >= 0; i--) {
        if (e->grelha[l][i] == PECA) {
            p1.lin = l;
            p1.col = i;
            altera (e,p,p1);
        }
        if (e->grelha[l][i] == VAZIA) break;
    }
    for (i = c + 1; i < 8; i++) {
        if (e->grelha[l][i] == PECA) {
            p1.lin = l;
                p1.col = i;
                altera (e,p,p1);
            }
        if (e->grelha[l][i] == VAZIA) break;
    }
    for (i = l-1 ; i>=0; i--) {
        if (e->grelha[i][c] == PECA) {
            p1.lin = i;
            p1.col = c;
            altera (e,p,p1);
        }
        if (e->grelha[i][c] == VAZIA) break;
    }
    for (i = l+1; i<8; i++) {
        if (e->grelha[i][c] == PECA) {
            p1.lin = i;
            p1.col = c;
            altera (e,p,p1);
        }
        if (e->grelha[i][c] == VAZIA) break;
    }
    for (i = l-1; i>=0; i--) {
        if (e->grelha[i][i] == PECA) {
            p1.lin = i;
            p1.col = i;
            altera (e,p,p1);
        }
        if (e->grelha[i][i] == VAZIA) break;
    }
    for (i = l+1; i<8; i++) {
        if (e->grelha[i][i] == PECA) {
            p1.lin = i;
            p1.col = i;
            altera (e,p,p1);
        }
        if (e->grelha[i][i] == VAZIA) break;
    }
    j = c+1;
    for (i = l-1; i>=0 && j<8; i--) {
        if (e->grelha[i][j] == PECA) {
            p1.lin = i;
            p1.col = j;
            altera (e,p,p1);
        }
        if (e->grelha[i][j] == VAZIA) break;
        j++;
    }
    j = c-1;
    for (i = l+1; i<8 && j>=0; i++) {
        if (e->grelha[i][j] == PECA) {
            p1.lin = i;
            p1.col = j;
            altera (e,p,p1);
        }
        if (e->grelha[i][j] == VAZIA) break;
        j--;
    }
    
}


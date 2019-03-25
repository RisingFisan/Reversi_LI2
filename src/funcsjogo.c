#include "estado.h"
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
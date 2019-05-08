#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "estado.h"
#include "bot.h"
#include "funcsjogo.h"

POSICAO jogadaBot(BOT* bot, ESTADO* e) {
    POSICAO jogadasP[60];
    POSICAO jogada = {0};
    srand(time(NULL));
    int jp = jogadasPossiveis(*e,e->peca,jogadasP);
    switch(bot->dif) {
        case 1: {
            jogada = jogadasP[rand() % (jp - 1)];
            break; }
        case 2:
            break;
        case 3: {
            int valor = -1000000000;
            for(int i = 0; i < jp; i++) {
                ESTADO eCpy = *e;
                jogar(&eCpy, jogadasP[i].lin, jogadasP[i].col);
                eCpy.peca = eCpy.peca == VALOR_X ? VALOR_O : VALOR_X;
                int x = minimax(eCpy, 5, bot->peca);
                if(x > valor) {
                    jogada = jogadasP[i];
                    valor = x;
                }
            }
            break; }
    }
    return jogada;
}

int max(int a, int b) {return a > b ? a : b; }
int min(int a, int b) {return a > b ? b : a; }

int minimax(ESTADO node, int depth, VALOR maximizingPlayer) {
    POSICAO jogadasP[60];
    int value;
    int jp = jogadasPossiveis(node,node.peca,jogadasP);
    if(depth == 0) {
        return valor(node,maximizingPlayer);
    }
    if(gameOver(node)) {
        int diff = score(node,maximizingPlayer) - score(node,maximizingPlayer == VALOR_X ? VALOR_O : VALOR_X);
        if(diff > 0)
            return 1000000;
        else if(diff < 0)
            return -1000000;
        else return 0;
    }
    if(node.peca == maximizingPlayer) {
        value = -1000000;
        if(jp == 0) {
            node.peca = node.peca = VALOR_X ? VALOR_O : VALOR_X;
            value = max(value, minimax(node, depth - 1, maximizingPlayer));
        }
        for(int i = 0; i < jp; i++) {
            ESTADO nodeCopy = node;
            jogar(&nodeCopy, jogadasP[i].lin, jogadasP[i].col);
            nodeCopy.peca = nodeCopy.peca = VALOR_X ? VALOR_O : VALOR_X;
            value = max(value, minimax(nodeCopy, depth - 1, maximizingPlayer));
        }
        return value;
    }
    else {
        value = 1000000;
        if(jp == 0) {
            node.peca = node.peca = VALOR_X ? VALOR_O : VALOR_X;
            value = min(value, minimax(node, depth - 1, maximizingPlayer));
        }
        for(int i = 0; i < jp; i++) {
            ESTADO nodeCopy = node;
            jogar(&nodeCopy, jogadasP[i].lin, jogadasP[i].col);
            nodeCopy.peca = nodeCopy.peca = VALOR_X ? VALOR_O : VALOR_X;
            value = min(value, minimax(nodeCopy, depth - 1, maximizingPlayer));
        }
        return value;
    }
}

int valor(ESTADO e, VALOR peca) {
    int soma = 0;
    int valor_pos[8][8]={{ 99, -8,  8,  6,  6,  8, -8, 99},
                         { -8,-24, -4, -3, -3, -4,-24, -8},
                         {  8, -4,  7,  4,  4,  7, -4,  8},
                         {  6, -3,  4,  0,  0,  4, -3,  6},
                         {  6, -3,  4,  0,  0,  4, -3,  6},
                         {  8, -4,  7,  4,  4,  7, -4,  8},
                         { -8,-24, -4, -3, -3, -4,-24, -8},
                         { 99, -8,  8,  6,  6,  8, -8, 99}};
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(e.grelha[i][j] == peca) 
                soma += valor_pos[i][j];
        }
    }
    return soma;
}
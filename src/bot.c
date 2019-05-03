#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "estado.h"
#include "bot.h"
#include "funcsjogo.h"

int jogadaBot(BOT* bot, ESTADO* e) {
    POSICAO jogadasP[60];
    srand(time(NULL));
    int jp = jogadasPossiveis(*e,e->peca,jogadasP);
    if(jp == 0) {
        printf("\nBot não pode jogar, teve de passar a vez.\n\n");
        return 1;
    }
    switch(bot->dif) {
        case 1: {
            POSICAO jogada = jogadasP[rand() % (jp - 1)];
            jogar(e,jogada.lin,jogada.col);
            break; }
        case 2:
            POSICAO jogada = {0};
            POSICAO aresta[24] = {0};
            POSICAO naoAres[36]= {0};
            int canto = 0;
            int numArestas = 0;
            int numNaoAres = 0;
            for(int i=0;i<jp;i++){
                if (jogadasP[i].lin==0 && jogadasP[i].col==0
                 || jogadasP[i].lin==0 && jogadasP[i].col==7
                 || jogadasP[i].lin==7 && jogadasP[i].col==0
                 || jogadasP[i].lin==7 && jogadasP[i].col==7 ) {
                    canto = 1;
                    jogada = jogadasP[i];
                    break;
                }
                else {
                    if (jogadasP[i].lin == 1
                        || jogadasP[i].col == 1
                        || jogadasP[i].lin == 8
                        || jogadasP[i].col == 8) {
                        aresta[numArestas++] = jogadasP[i];
                    }
                    else naoAres[numNaoAres++]=jogadasP[i];
                }
            }

            if (canto==0) {
                if (numArestas) {
                    jogada = aresta[0];
                    for (int i = 1; i < numArestas; i++) {
                        if (aresta[i].dest > jogada.dest) jogada = aresta[i];
                    }
                } else {
                    jogada = naoAres[0];
                    for (int i = 1; i < numNaoAres; i++) {
                        if (naoAres[i].dest > jogada.dest) jogada = naoAres[i];
                    }
                }
            }
            jogar(e,jogada.lin,jogada.col);
            break;
        case 3: {
            POSICAO jogada = {0};
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
            jogar(e,jogada.lin,jogada.col);
            break; }
    }
    return 0;
}

int max(int a, int b) {return a > b ? a : b; }
int min(int a, int b) {return a > b ? b : a; }

int minimax(ESTADO node, int depth, VALOR maximizingPlayer) {
    POSICAO jogadasP[60];
    int value;
    int jp = jogadasPossiveis(node,node.peca,jogadasP);
    if(depth == 0 || jp == 0) {
        return valor(node,maximizingPlayer);
    }
    if(node.peca == maximizingPlayer) {
        value = -1000000000;
        for(int i = 0; i < jp; i++) {
            ESTADO nodeCopy = node;
            jogar(&nodeCopy, jogadasP[i].lin, jogadasP[i].col);
            nodeCopy.peca = nodeCopy.peca = VALOR_X ? VALOR_O : VALOR_X;
            value = max(value, minimax(nodeCopy, depth - 1, maximizingPlayer));
        }
        return value;
    }
    else {
        value = 1000000000;
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
    int valor_pos[8][8]={{ 99,-24,  8,  6,  6,  8,-24, 99},
                         {-24,-50, -4, -3, -3, -4,-50,-24},
                         {  8, -4,  7,  4,  4,  7, -4,  8},
                         {  6, -3,  4,  0,  0,  4, -3,  6},
                         {  6, -3,  4,  0,  0,  4, -3,  6},
                         {  8, -4,  7,  4,  4,  7, -4,  8},
                         {-24,-50, -4, -3, -3, -4,-50,-24},
                         { 99,-24,  8,  6,  6,  8,-24, 99}};
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(e.grelha[i][j] == peca) 
                soma += valor_pos[i][j];
        }
    }
    return soma;
}
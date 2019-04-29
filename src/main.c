#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "estado.h"
#include "funcsjogo.h"
#include "saveload.h"
#include "bot.h"

int main() {
    ESTADO e = {0};
    ESTADOSH historico = malloc(sizeof(struct estadosh));
    historico = NULL;

    BOT bot = {0};

    int quit = 0;
    int inGame = 0;
    char linha[50];
    char c1;
    int x, y, jp = 0, jogInv = 0;
    int* ajudaPos = malloc(sizeof(int));
    *ajudaPos = 0;
    POSICAO jogadasP[60] = {0};

    while(!quit) {
        jp = jogadasPossiveis(e,e.peca,jogadasP);
        if(jp == 0 && inGame) {
            if(!jogadasPossiveis(e,e.peca == VALOR_X ? VALOR_O : VALOR_X,jogadasP)) {
                printf("\nNão há mais jogadas possíveis! GAME OVER\n");
                int sx = score(e,VALOR_X);
                int so = score(e,VALOR_O);
                if(sx==so) printf("EMPATE!");
                else printf("VENCEDOR: %c",sx > so ? 'X' : 'O');
                break;
            }
            else {
                printf("\nJogador %c não pode jogar, tem de passar a vez.\n\n",e.peca == VALOR_X ? 'X' : 'O');
                e.peca = e.peca == VALOR_O ? VALOR_X : VALOR_O;
                jp = jogadasPossiveis(e,e.peca,jogadasP);
                if(e.modo == 1 && e.peca == bot.peca) {
                    if(!jogadaBot(&bot,&e)) {
                        printf("Jogada do bot:\n");
                        printa(e, ajudaPos, jp, jogadasP);
                        printf("X: %2d       O: %2d\n\n",score(e,VALOR_X),score(e,VALOR_O));
                    }
                    e.peca = e.peca == VALOR_O ? VALOR_X : VALOR_O;
                }
            }
        }
        if(!inGame) printf("> ");
        else printf("%c> ",e.peca == VALOR_X ? 'X' : 'O');
        fgets(linha,50,stdin);
        switch(toupper(linha[0])) {
            case 'N':
                e.modo = 0;
                sscanf(linha + 1," %c",&c1);
                newBoard(&e,toupper(c1) == 'X' ? VALOR_X : VALOR_O,0);
                inGame = 1;
                limpaHist(&historico);
                break;
            case 'J':
                sscanf(linha + 1,"%d %d",&y,&x);
                y--;
                x--;
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
                        break;
                    }
                }
                if(jogInv) printf("\nJogada inválida! Tente novamente.\n\n");
                break;
            case 'S':
                *ajudaPos = 1;
                break;
            case 'E': {
                if(grava(e,strtok(linha + 2,"\n"))) printf("\nErro ao guardar ficheiro.\n\n");
                else printf("\nFicheiro guardado com sucesso!\n\n");
                break; }
            case 'L':
                if(!carrega(&e,strtok(linha + 2,"\n"))) {
                    if(e.modo == 1) {
                        bot.peca = e.peca == VALOR_X ? VALOR_O : VALOR_X;
                        bot.dif = e.dif;
                    }
                    printf("\nJogo carregado com sucesso!\n\n");
                    inGame = 1;
                }
                else printf("\nErro ao carregar jogo, ficheiro não encontrado.\n\n");
                limpaHist(&historico);
                break;
            case 'U':
                if(historico) {
                    e = historico->e;
                    ESTADOSH temp = historico;
                    historico = historico->prox;
                    free(temp);
                }
                else printf("\nImpossível anular jogada.\n\n");
                break;
            case 'A':
                sscanf(linha + 1," %c %d",&c1,&x);
                bot.peca = toupper(c1) == 'X' ? VALOR_X : VALOR_O;
                newBoard(&e,VALOR_X,1);
                while(x < 1 || x > 3) {
                    printf("\n\nDificuldade inválida - introduza um valor entre 1 e 3!\n\n> ");
                    scanf("%d",&x);
                }
                limpaHist(&historico);
                e.dif = bot.dif = x;
                inGame = 1;
                break;
            case 'Q':
                quit = 1;
                break;

        }
        if(inGame && !quit) {
            printa(e, ajudaPos, jp, jogadasP);
            printf("X: %2d       O: %2d\n\n",score(e,VALOR_X),score(e,VALOR_O));
        }
        if(e.modo == 1 && e.peca == bot.peca) {
            if(!jogadaBot(&bot,&e))
                printf("Jogada do bot:\n");
            printa(e, ajudaPos, jp, jogadasP);
            printf("X: %2d       O: %2d\n\n",score(e,VALOR_X),score(e,VALOR_O));
            e.peca = e.peca == VALOR_O ? VALOR_X : VALOR_O;
        }
        jogInv = 0;
    }
    return 0;
}
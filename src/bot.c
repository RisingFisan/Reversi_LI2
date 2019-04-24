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
            break;
        case 3:
            break;
    }
    return 0;
}
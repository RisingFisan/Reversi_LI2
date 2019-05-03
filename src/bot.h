#include "estado.h"

/**
 * Estrutura que armazena as características de um 'bot', i.e., um jogador controlado pelo computador.
 */
typedef struct bot {
    char dif; ///< a dificuldade do bot
    VALOR peca; ///< a peça com que o bot joga
} BOT;

int jogadaBot(BOT* bot, ESTADO* e);

int valor(ESTADO e);

int minimax(ESTADO node, int depth, VALOR maximizingPlayer);

int max(int a, int b);
int min(int a, int b);
#include "estado.h"

/** \mainpage Documentação
 * 
 * \section intro_sec Introdução 
 * 
 * Introdução
 * 
 * 
 * 
 * 
 * 
 * 
 */


/**
 * \brief Estrutura que armazena as características de um 'bot', i.e., um jogador controlado pelo computador.
 * 
 * Um bot é caracterizado pela sua dificuldade e pela peça com que joga. A partir destes dois dados, podemos criar um jogador autónomo, que usa algoritmos para calcular onde deve jogar.
 */
typedef struct bot {
    char dif; ///< a dificuldade do bot
    VALOR peca; ///< a peça com que o bot joga
} BOT;

POSICAO jogadaBot(BOT* bot, ESTADO* e);

int valor(ESTADO e, VALOR peca);

int minimax(ESTADO node, int depth, int alpha, int beta, VALOR maximizingPlayer);

int max(int a, int b);
int min(int a, int b);
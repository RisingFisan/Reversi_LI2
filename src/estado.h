//
// Created by pja on 27/02/2019.
//



#ifndef PROJ_ESTADO_H
#define PROJ_ESTADO_H



/**
estado.h
Definição do estado i.e. tabuleiro. Representação matricial do tabuleiro.
*/


/** definição de valores possiveis no tabuleiro 
@param VAZIA casa vazia
@param VALOR_X casa ocupada por uma peça X
@param VALOR_O casa ocupada por uma peça O
*/
typedef enum {VAZIA, VALOR_X, VALOR_O} VALOR;

/*!
 * @brief Estrutura que armazena o estado do jogo
 * 
 * Um estado contém todas as informações do jogo, em especial o tabuleiro. Assim, para guardar o jogo, basta apenas guardar o estado atual.
 */
typedef struct estado {
    VALOR peca; ///< peça do jogador que vai jogar!
    VALOR grelha[8][8]; ///< tabuleiro do jogo
    char modo; ///< tipo de jogo! 0-> manual, 1-> contra o computador
    char dif; ///< dificuldade do jogo (quando em modo automático, contra o computador), entre 1 e 3.
} ESTADO;

/**
Estrutura dinâmica (lista ligada) que armazena o histórico do jogo, i.e., todas as jogadas anteriores.
@param e estado armazenado na lista
@param prox apontador para o resto da lista
*/
typedef struct estadosh {
    ESTADO e;
    struct estadosh * prox;
} *ESTADOSH;

/**
Estrutura que armazena uma posição da grelha.
@param lin linha da posição
@param col coluna da posição
@param dest "poder destrutivo" da posição, i.e., quantas peças rivais uma peça "come" se for colocada nessa posição
*/
typedef struct posicao {
    char lin;
    char col; 
    char dest;
} POSICAO;

/**
Imprime no terminal o tabuleiro do jogo, com as peças no seu lugar.
@param e estado onde está guardado o tabuleiro.
@param pVal se for 1, indica com um '.' as posições onde o jogador atual pode jogar.
@param nPos número de posições válidas, i.e., onde o jogador atual pode jogar.
@param pos lista com as posições válidas para o jogador atual.
 */
void printa(ESTADO e, int* pVal, int nPos, POSICAO pos[]);

void newBoard(ESTADO* e, VALOR peca, char modo);

void limpaHist(ESTADOSH* hist);

#endif //PROJ_ESTADO_H
#include "estado.h"

#ifndef PROJ_FUNCSJOGO_H
#define PROJ_FUNCSJOGO_H

int score(ESTADO e, VALOR peca);

int jogadasPossiveis(ESTADO e, VALOR peca, POSICAO pos[]);
int jogadaH(ESTADO e, VALOR peca, POSICAO* p);
int jogadaV(ESTADO e, VALOR peca, POSICAO* p);
int jogadaD(ESTADO e, VALOR peca, POSICAO* p);

void jogar (ESTADO* e, int c,int l);

#endif // PROJ_FUNCSJOGO_H
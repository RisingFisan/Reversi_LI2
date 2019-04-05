#include <stdio.h>
#include <string.h>
#include "estado.h"

int grava(ESTADO e, char* fileName, int N, POSICAO* jps) {
    FILE *f;
    if((f = fopen(strcat(fileName,".txt"), "w")) == NULL) return 1;
    else {

        if (e.modo == '0') fprintf(f, "M ");
        else               fprintf(f, "A ");

        if (e.peca == VALOR_X) fprintf(f, "X\n");
        else                   fprintf(f, "O\n");

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                int printed = 0;
                for(int k = 0; k < N; k++) {
                    if(jps[k].lin == i && jps[k].col == j) {   fprintf(f, ". ");
                                                               printed = 1; }
                }
                if(!printed) {
                    if (e.grelha[i][j] == VAZIA)               fprintf(f, "_ ");
                    else if (e.grelha[i][j] == VALOR_X)        fprintf(f, "X ");
                    else                                       fprintf(f, "O ");
                }
            }
            fprintf(f, "\n");
        }
        fclose(f);
        return 0;
    }
}

int carrega (ESTADO *e, char *s){
	FILE *f;
	char a,b,c;
	f=fopen(strcat(s,".txt"), "r");
	if (f==NULL) return 1;
	else {
	    fscanf(f,"%c %c\n",&a,&b);
		if (a=='M') e->modo='0';
		else e->modo='1';
		if (b=='X') e->peca=VALOR_X;
		else e->peca=VALOR_O;
		    for (int i=0;i<8;i++){
		 	   for(int j=0;j<8;j++){
		 		   fscanf(f,"%c ",&c);
		 		   if (c=='X') e->grelha[i][j]=VALOR_X;
		 		   else if (c=='O') e->grelha[i][j]=VALOR_O;
		 		   else e->grelha[i][j]=VAZIA;
		 	}
		    fprintf(f, "\n");
		 }

	}
	fclose(f);
	return 0;
}



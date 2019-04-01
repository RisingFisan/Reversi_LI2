#include<stdio.h>
#include "estado.h"

void grava (ESTADO e){
    FILE *f;
f = fopen("tabuleiro.txt", "w");
if (e.modo=='0') fprintf(f,"M ");
else fprintf(f,"A");
if (e.peca==VALOR_X) fprintf(f,"X\n");
else fprintf(f,"O\n");
      for(int i=0;i<8;i++){
         for(int j=0;j<8;j++){
           	if (e.grelha[i][j]==VAZIA) fprintf(f,"_");
            else if (e.grelha[i][j]==VALOR_X)
                fprintf(f,"X");
            else fprintf(f,"O");
            }
 fprintf(f,"\n");
            }

 fclose(f);
          }

 
 /*int main() {
  ESTADO e;
  e.peca= VALOR_X;
  e.modo='0';
  for(int i=0;i<8;i++) {
  	for(int j=0;j<8;j++) {
  		e.grelha[i][j] = VALOR_X;
  	}
  }
  grava (e);
 
  
return 0;
 }*/


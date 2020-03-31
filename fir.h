#include "define.h"
#include "fichiers.h"
/*! ------------------------------------------------------------

  \struct param_fir

  \brief

  ------------------------------------------------------------*/

typedef struct{
    float led[51];      //contient les valeurs de ACR
    float infrarouge[51];   //contient les valeurs de ACIR
    int index;      //permet de savoir à quel "n" nous sommes
}param_fir;

/***********function****************/

param_fir* init_fir();

absorp fir(absorp myAbsorp,param_fir* myFIR);

void fin_fir(param_fir* myFIR) ;

absorp firTest(char* filename);
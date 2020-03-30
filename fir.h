#include "define.h"

/*! ------------------------------------------------------------

  \struct param_fir

  \brief

  ------------------------------------------------------------*/

typedef struct{
    float led[51];
    float infrarouge[51];
    int index;
}param_fir;

/***********function****************/

param_fir init_fir();
absorp fir(absorp myAbsorp,param_fir myFIR);
void fin_fir(param_fir* myFIR) ;
absorp firTest(char* filename);
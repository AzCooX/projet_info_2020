#include "define.h"
/*! ------------------------------------------------------------

  \struct param_iir

  \brief

  ------------------------------------------------------------*/

typedef struct{
    float led;
    float infrarouge;
    float lastEntryLed;
    float lastEntryInfrarouge;
    float lastLed;
    float lastInfrarouge;
}param_iir;

/***********function****************/

param_iir* init_iir();

absorp iir(absorp myAbsorp,param_iir* myFIR);

void fin_iir(param_iir* myFIR) ;

absorp iirTest(char* filename);
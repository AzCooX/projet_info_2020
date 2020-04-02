#include "define.h"
#include "fichiers.h"
/*! ------------------------------------------------------------

  \struct param_iir

  \brief

  ------------------------------------------------------------*/

typedef struct{
    float led;      //stocke la nouvelle valeur d'ACR suite au filtrage
    float infrarouge;   //stocke la nouvelle valeur d'ACIR suite au filtrage
    float lastEntryLed; //stocke la dernière entrée ACR
    float lastEntryInfrarouge;  //stocke la dernière entrée ACIR
    float lastLed;      //stocke la dernière valeur de led
    float lastInfrarouge;   //stocke la dernière valeur d'infrarouge
}param_iir;

/***********function****************/

param_iir* init_iir();

absorp iir(absorp myAbsorp,param_iir* myIIR);

void fin_iir(param_iir* myIIR) ;

absorp iirTest(char* filename);
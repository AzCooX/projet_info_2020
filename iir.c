#include "iir.h"
#include "fichiers.h"
param_iir* init_iir(){
    param_iir* myIIR = (param_iir*)malloc(1*sizeof(param_iir));
    myIIR->led=0;
    myIIR->infrarouge=0;
    myIIR->lastLed=0;
    myIIR->lastInfrarouge=0;
    myIIR->lastEntryLed=0;
    myIIR->lastEntryInfrarouge=0;
    return myIIR;
}

absorp iir(absorp myAbsorp,param_iir* myIIR){
myIIR->led=myAbsorp.acr-myIIR->lastEntryLed+0.992*myIIR->lastLed;
myIIR->lastEntryLed=myAbsorp.acr;
myIIR->lastLed=myIIR->led;
myAbsorp.acr=myIIR->led;

myIIR->infrarouge=myAbsorp.acir-myIIR->lastEntryInfrarouge+0.992*myIIR->lastInfrarouge;
myIIR->lastEntryInfrarouge=myAbsorp.acir;
myIIR->lastInfrarouge=myIIR->infrarouge;
myAbsorp.acir=myIIR->infrarouge;
}

void fin_iir(param_iir* myIIR){
    free(myIIR);
}
absorp iirTest(char* filename){
    int etat=0;
	absorp	myAbsorp;
	FILE* myfile = initFichier(filename);
    param_iir* myIIR= init_iir();
	myAbsorp=lireFichier(myfile,&etat);
	finFichier(myfile);
    myAbsorp= iir(myAbsorp,myIIR);
	return myAbsorp;

}


#include "iir.h"

param_iir* init_iir(){      //initialise les membres d'une structure param_iir
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
myIIR->led=myAbsorp.acr-myIIR->lastEntryLed+0.992*myIIR->lastLed;   //application de la formule de filtrage pour ACR
myIIR->lastEntryLed=myAbsorp.acr;
myIIR->lastLed=myIIR->led;
myAbsorp.acr=myIIR->led;

myIIR->infrarouge=myAbsorp.acir-myIIR->lastEntryInfrarouge+0.992*myIIR->lastInfrarouge; //application de la formule de filtrage pour ACIR
myIIR->lastEntryInfrarouge=myAbsorp.acir;
myIIR->lastInfrarouge=myIIR->infrarouge;
myAbsorp.acir=myIIR->infrarouge;

return myAbsorp;
}

void fin_iir(param_iir* myIIR){     //libère l'espace mémoire alloué dans le init
    free(myIIR);
}
absorp iirTest(char* filename){
    int etat=0;
    param_iir* myIIR = init_iir();
	absorp	myAbsorp;
	FILE* myFile = initFichier(filename);
    do
    {
        absorp readData = lireFichier(myFile, &etat); //Lecture des données
        if(!(readData.dcir == 0 && readData.dcr == 0 && readData.acir == 0 && readData.acr == 0)) //On vérifie que les données sont valides
        {
            myAbsorp = iir(readData, myIIR); //Filtrage IIR pour ACR et ACIR
            printf("valeur ACR: %f\n",myAbsorp.acr);
            printf("valeur ACIR: %f\n",myAbsorp.acir);
        }
    }
    while(etat != EOF);
    fin_iir(myIIR);
	finFichier(myFile);
    return myAbsorp;
}


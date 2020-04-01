#include "integration.h"

void integrationTest(char* filename)    //rien include dans .h et tout dans .c?
{
    int etat=0;
    absorp myAbsorp;
    oxy myOxy;
    param_fir* myFIR= init_fir();// init FIR
    param_iir* myIIR= init_iir(); // init IIR
    param_mesure* myMes= init_mesure(); //init mesure
    FILE* myFile=initFichier("record1.dat");
    do{
        myAbsorp= lireFichier(myFile,&etat);
        myAbsorp= fir(myAbsorp,myFIR);
        myAbsorp= iir(myAbsorp,myIIR);
        myOxy= mesure(myOxy,myAbsorp,myMes);
        affichage(myOxy);
    }while( etat!= EOF);
    finFichier(myFile);
    fin_mesure(myMes);
    fin_iir(myIIR);
    fin_fir(myFIR) ;
}
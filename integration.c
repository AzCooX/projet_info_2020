#include "integration.h"
#include "define.h"
#include "affichage.h"
#include "iir.h"
#include "fir.h"
#include "mesure.h"
void integrationTest(char* filename)    //rien include dans .h et tout dans .c?
{
    int etat=0;
    absorp myAbsorp;
    oxy myOxy;
    param_fir* myFIR= init_fir();// init FIR
    param_iir* myIIR= init_iir(); // init IIR
    param_mesure* myMes= init_mesure(); //init mesure
    FILE* myFile=initFichier(filename);
    do{
        myAbsorp= lireFichier(myFile,&etat);
        if(!(myAbsorp.dcir == 0 && myAbsorp.dcr == 0 && myAbsorp.acir == 0 && myAbsorp.acr == 0)) //On vérifie que les données sont valides
        {
            myAbsorp = fir(myAbsorp, myFIR);
            myAbsorp = iir(myAbsorp, myIIR);
            myOxy= mesure(myAbsorp,myMes);
           // printf("valeur SPO2: %d\n",myOxy.spo2);
            //printf("valeur Pouls: %d\n",myOxy.pouls);
            affichage(myOxy);
        }
    }while( etat!= EOF);
    finFichier(myFile);
    fin_mesure(myMes);
    fin_iir(myIIR);
    fin_fir(myFIR) ;
}
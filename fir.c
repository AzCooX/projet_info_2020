#include "fir.h"

double coef[51]={1.4774946e-019,1.6465231e-004,3.8503956e-004,7.0848037e-004,1.1840522e-003,1.8598621e-003,2.7802151e-003,
                3.9828263e-003,5.4962252e-003,7.3374938e-003,9.5104679e-003,1.2004510e-002,1.4793934e-002,1.7838135e-002,
                2.1082435e-002,2.4459630e-002,2.7892178e-002,3.1294938e-002,3.4578348e-002,3.7651889e-002,4.0427695e-002,
                4.2824111e-002,4.4769071e-002,4.6203098e-002,4.7081811e-002,4.7377805e-002,4.7081811e-002,4.6203098e-002,
                4.4769071e-002,4.2824111e-002,4.0427695e-002,3.7651889e-002,3.4578348e-002,3.1294938e-002,2.7892178e-002,
                2.4459630e-002,2.1082435e-002,1.7838135e-002,1.4793934e-002,1.2004510e-002,9.5104679e-003,7.3374938e-003,
                5.4962252e-003,3.9828263e-003,2.7802151e-003,1.8598621e-003,1.1840522e-003,7.0848037e-004,3.8503956e-004,
                1.6465231e-004,1.4774946e-019};

param_fir* init_fir(){
    int i;
    param_fir* myFIR = (param_fir*)malloc(1*sizeof(param_fir));
    for(i=0;i<=50;i++){     //initialise le tableau led à 0
        myFIR->led[i]=0;
        myFIR->infrarouge[i]=0;
    }
    myFIR->index=0;
    return myFIR;
}

absorp fir(absorp myAbsorp,param_fir* myFIR){
    int i;
    int position;
    myFIR->led[myFIR->index]=myAbsorp.acr;
    myFIR->infrarouge[myFIR->index]=myAbsorp.acir;
    myAbsorp.acr=0;
    myAbsorp.acir=0;
    for(i=0;i<=50;i++) {
        position = myFIR->index-i;
        if(position<0){
            position+=51;
        }
        myAbsorp.acr += coef[i] * myFIR->led[position];     //pas sur
        myAbsorp.acir += coef[i] * myFIR->infrarouge[position];
    }
    myFIR->index=((myFIR->index)+1)%50;
    return myAbsorp;
}

void fin_fir(param_fir* myFIR){
    free(myFIR);
}

absorp firTest(char* filename){
	absorp	myAbsorp;
    int etat=0;
    param_fir* myFIR = init_fir();
    FILE* myFile = initFichier(filename);
    do
    {
        absorp readData = lireFichier(myFile, &etat); //Lecture des données
        if(!(readData.dcir == 0 && readData.dcr == 0 && readData.acir == 0 && readData.acr == 0)) //On vérifie que les données sont valides
        {
            myAbsorp = fir(readData, myFIR); //Filtrage FIR pour ACR et ACIR
            printf("valeur ACR: %f\n",myAbsorp.acr);
            printf("valeur ACIR: %f\n",myAbsorp.acir);
        }
    }
    while(etat != EOF);
    fin_fir(myFIR);
    finFichier(myFile);

	return myAbsorp;

}
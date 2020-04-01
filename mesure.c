#include "mesure.h"

param_mesure* init_mesure(){
    int i;
	param_mesure* myMes = (param_mesure*)malloc(1*sizeof(param_mesure));
	myMes->lastMaximumACR=0;
	myMes->lastMinimumACR=0;
    myMes->lastMaximumACIR=0;
    myMes->lastMinimumACIR=0;
	myMes->compteur=0;
	myMes->previousVal=0;
	myMes->indexPouls=0;
	myMes->pouls=0;
	myMes->spo2=0;
	for(i=0;i<10;i++){
        myMes->oldPouls[i]=0;
	}
	return myMes;
}
void fin_mesure(param_mesure* myMes){
	free(myMes);
}

oxy mesure(absorp myAbsorp, param_mesure* myMes){

	oxy myOxy;
	float frequence;	//Calcul du pouls   ( pas oublier de faire la moyenne)
	float ptpACR;
	float ptpACIR;
	float ratio;
	int a,b;
	if(myMes->previousVal<myAbsorp.acr && (myMes->previousVal)/(myAbsorp.acr)<0){	// si la nouvelle valeur et l'ancienne sont de signes opposés et que on est sur un front montant
		frequence=(float)(1/((myMes->compteur)*0.002));
		frequence=frequence*60;     //obtention BPM
		myMes->compteur=0;
		myOxy.pouls=(int)frequence;
		myMes->pouls=(int)frequence;

	}else{
		myOxy.pouls=myMes->pouls;
	}
	myMes->previousVal=myAbsorp.acr;
	myMes->compteur=myMes->compteur+1;

	//Calcul SPO2

	if(myAbsorp.acr>myMes->lastMaximumACR){
		myMes->lastMaximumACR=myAbsorp.acr;
	}
	if(myAbsorp.acr<myMes->lastMinimumACR){
	    myMes->lastMinimumACR=myAbsorp.acr;
	}
    if(myAbsorp.acir>myMes->lastMaximumACIR){
        myMes->lastMaximumACIR=myAbsorp.acir;
    }
    if(myAbsorp.acir<myMes->lastMinimumACIR){
        myMes->lastMinimumACIR=myAbsorp.acir;
    }
    ptpACR=(myMes->lastMaximumACR)-(myMes->lastMinimumACR);
    ptpACIR=(myMes->lastMaximumACIR)-(myMes->lastMinimumACIR);
    ratio=(ptpACR/myAbsorp.dcr)/(ptpACIR/myAbsorp.dcir);
    if(ratio >= 0.4f && ratio <= 1.0f)
    {
        b = 110;
        a = -25;
    }
    else
    {
        b = 121.42857;
        a = -35.7142857;
    }
    myOxy.spo2 = ((int) (a*ratio + b));
    if(myMes->previousVal<myAbsorp.acir && (myMes->previousVal)/(myAbsorp.acir)<0){
        myMes->lastMinimumACIR=0;
        myMes->lastMaximumACIR=0;
        myMes->lastMinimumACR=0;
        myMes->lastMaximumACR=0;
    }
	return myOxy;

}

oxy mesureTest(char* filename){
	int etat=0;
	param_mesure* myMes = init_mesure();
	oxy myOxy;
	myOxy.spo2=0;
	myOxy.pouls=0;
	FILE* myFile = initFichier(filename);
	do
	{
		absorp readData = lireFichier(myFile, &etat); //Lecture des données
		if(!(readData.dcir == 0 && readData.dcr == 0 && readData.acir == 0 && readData.acr == 0)) //On vérifie que les données sont valides
		{
			myOxy = mesure(readData, myMes); //Calcul de SPO2 et du pouls
			printf("valeur SPO2: %d\n",myOxy.spo2);
			printf("valeur Pouls: %d\n",myOxy.pouls);
		}
	}
	while(etat != EOF);
	fin_mesure(myMes);
	finFichier(myFile);
	return myOxy;
}

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
	float frequence;
	float ptpACR;   //stocke la valeur peak to peak d'ACR
	float ptpACIR;  //stocke la valeur peak to peak d'ACIR
	float ratio;
	int a,b,i;
	int moyenne=0;

	//calcul Pouls

	if(myMes->previousVal<myAbsorp.acr && (myMes->previousVal)/(myAbsorp.acr)<0){	// si la nouvelle valeur et l'ancienne sont de signes opposés et que on est sur un front montant
		frequence=(float)(1/((myMes->compteur)*0.002));
		frequence=frequence*60;     //obtention BPM
		myMes->compteur=0;
		myMes->oldPouls[(myMes->indexPouls%10)]=(int)frequence;
		myMes->indexPouls++;
		for(i=0;i<10;i++){
			moyenne=moyenne+myMes->oldPouls[i];
		}

		if(myMes->indexPouls<10){
			moyenne=(moyenne/myMes->indexPouls);
		}else{
			moyenne=moyenne/10;
		}
		myOxy.pouls=moyenne;
		myMes->pouls=moyenne;
		printf("valeur Pouls: %d\n",myOxy.pouls);
	}else{
		myOxy.pouls=myMes->pouls;
	}

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
    ratio=(ptpACR/(myAbsorp.dcr));
    ratio=ratio/(ptpACIR/(myAbsorp.dcir));
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
	myMes->previousVal=myAbsorp.acr;
	myMes->compteur=myMes->compteur+1;
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

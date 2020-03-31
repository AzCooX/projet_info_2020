#include "mesure.h"

param_mesure* init_mesure(){
	param_mesure* myMes = (param_mesure*)malloc(1*sizeof(param_mesure));
	myMes->lastMaximum=0;
	myMes->lastMinimum=0;
	myMes->compteur=0;
	myMes->previousVal=0;
}
void fin_mesure(param_mesure* myMes){
	free(myMes);
}

oxy mesure(oxy myOxy,absorp myAbsorp, param_mesure* myMes){
	//Calcul du pouls   ( pas oublier de faire la moyenne)
	float test;
	if(myMes->previousVal<myAbsorp.acr && (myMes->previousVal)/(myAbsorp.acr)<0){	// si la nouvelle valeur et l'ancienne sont de signes opposés et que on est sur un front montant
		test=(float)(1/((myMes->compteur)*0.002));
		test=test*60;
		myOxy.pouls=test;
		myMes->compteur=0;
	}
	myMes->previousVal=myAbsorp.acr;
	myMes->compteur=myMes->compteur+1;

	//Calcul SPO2


	return myOxy;

}

oxy mesureTest(char* filename){
	int etat=0;
	param_mesure* myMes = init_mesure();
	oxy myOxy;
	FILE* myFile = initFichier(filename);
	do
	{
		absorp readData = lireFichier(myFile, &etat); //Lecture des données
		if(!(readData.dcir == 0 && readData.dcr == 0 && readData.acir == 0 && readData.acr == 0)) //On vérifie que les données sont valides
		{
			myOxy = mesure(myOxy,readData, myMes); //Calcul de SPO2 et du pouls
			printf("valeur SPO2: %d\n",myOxy.spo2);
			printf("valeur Pouls: %d\n",myOxy.pouls);
		}
	}
	while(etat != EOF);
	fin_mesure(myMes);
	finFichier(myFile);
	return myOxy;
}

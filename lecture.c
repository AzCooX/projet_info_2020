#include "lecture.h"

int lectureTest(){
	int etat = 0;
	FILE* file = fopen("lectureTest.txt","r");
	absorp test = lecture(file,&etat);

	if(test.acir == 2219 && test.acr == 2241 && test.dcr == 2030 && test.dcir == 2030){
	}
	else{
		return 0;
	}

	test = lecture(file,&etat);
	if(test.acir == 2183 && test.acr == 2185  && test.dcr == 2029 && test.dcir == 2029){
		return 1;
	}
	else{
		return 0;
	}


}

absorp lecture(FILE* file_pf, int* file_state){

	absorp myAbsorp;
	*file_state=EOF;

	char trame[21] = "";						// Je récupère une trame (donc ligne de fichier dans notre cas)
	fgets(trame,21,file_pf);					// dans un char* trame

	char* acr = malloc(4*sizeof(char));			// Je déclare ensuite 4 char* différents correspondant
	char* dcr = malloc(4*sizeof(char));			// aux 4 valeurs différentes à récupérer
	char* acir = malloc(4*sizeof(char));
	char* dcir = malloc(4*sizeof(char));

	int count=0;								// J'initialise un compteur qui va nous permettre
												// de sélectionner la chaine où on souhaite écrire

	int i=0;
	for(i=0; i<21; i++) {
		if ((i+1)%5 ==0) {                    	// Tous les 4 octets, une virgule sépare les valeurs
			count++;							// on incrémente donc la valeur du compteur
		} else {
			switch (count) {
				case 0:
					acr[i] = trame[i];
					break;
				case 1:
					dcr[i-(4*count)-1] = trame[i];
					break;
				case 2:
					acir[i-(4*count)-2] = trame[i];
					break;
				case 3:
					dcir[i-(4*count)-3] = trame[i];
					break;
				default:
					break;
			}
		}
	}
	char * endptr;

	myAbsorp.acir = strtof(acir,&endptr);		// Il ne reste plus qu'à assigner les différentes
	myAbsorp.dcir = strtof(dcir,&endptr);		// valeurs à la structure myAbsorb en convertissant
	myAbsorp.acr = strtof(acr,&endptr);			// les char* en float
	myAbsorp.dcr = strtof(dcr,&endptr);

	char nextline[200] = "";
	fgets(nextline,200,file_pf);				// On enlève les derniers caractères de la ligne inutilisés
	fgets(nextline,,200,file_pf);				// On saute la ligne séparant les deux trames

	return myAbsorp; // return EOF flag
}


#include "lecture.h"

absorp lecture(FILE* file_pf, int* file_state) {

    absorp myAbsorp;
    char trame[21];                                 // Je crée une chaine de 22 caractères en incluant
    int i;
    int validTrame = 2;

    do{
        for (i=0; i < 21; i++) {
            trame[i] = fgetc(file_pf);              // On copie le caractère dans le buffer

            if(trame[i] == EOF){                     // Si le caractère est un CR on relance à
                *file_state = EOF;
                validTrame = 1;
            }
            else if(trame[i] == 13){               // Si fin du fichier on change l'état de file_state
                if(i == 20){
                    validTrame = 1;
                }
                else{
                    i = -1;
                }
            }
        }

    }while (validTrame != 1);

    if (*file_state != EOF) {
        char *acr = malloc(5 * sizeof(char));       // Je déclare ensuite 4 char* différents correspondant
        char *dcr = malloc(5 * sizeof(char));       // aux 4 valeurs différentes à récupérer
        char *acir = malloc(5 * sizeof(char));
        char *dcir = malloc(5 * sizeof(char));

        int count = 0;                              // J'initialise un compteur qui va nous permettre
        // de sélectionner la chaine où on souhaite écrire
        for (i = 0; i < 21; i++) {
            if ((i + 1) % 5 == 0) {                 // Tous les 4 octets, une virgule sépare les valeurs
                count++;                            // on incrémente donc la valeur du compteur
            } else {
                switch (count) {
                    case 0:
                        acr[i] = trame[i];
                        break;
                    case 1:
                        dcr[i - (4 * count) - 1] = trame[i];
                        break;
                    case 2:
                        acir[i - (4 * count) - 2] = trame[i];
                        break;
                    case 3:
                        dcir[i - (4 * count) - 3] = trame[i];
                        break;
                    default:
                        break;
                }
            }
        }
        char *endptr;

        acr[5] = '\0';                // On signale la fin de chaine de caractères avec '\0'
        dcr[5] = '\0';
        acir[5] = '\0';
        dcir[5] = '\0';

        myAbsorp.acir = strtof(acir, &endptr) - 2048;      // Il ne reste plus qu'à assigner les différentes
        myAbsorp.dcir = strtof(dcir, &endptr);      // valeurs à la structure myAbsorb en convertissant
        myAbsorp.acr = strtof(acr, &endptr) - 2048;        // les char* en float
        myAbsorp.dcr = strtof(dcr, &endptr);

        free(acir);                                 // Enfin, on désalloue l'espace mémoire occupé
        free(acr);                                  // par nos chaines de caractères
        free(dcr);
        free(dcir);

        return myAbsorp;                            // return EOF flag*

    } else {
        myAbsorp.acir = 0;      // Il ne reste plus qu'à assigner les différentes
        myAbsorp.dcir = 0;      // valeurs à la structure myAbsorb en convertissant
        myAbsorp.acr = 0;        // les char* en float
        myAbsorp.dcr = 0;

        return myAbsorp;
    }
}

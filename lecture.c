#include "lecture.h"

absorp lecture(FILE* file_pf, int* file_state) {

    absorp myAbsorp;
    char trame[21];                                 // Je crée un buffer de 21 caractères
    int i;
    int validTrame = 2;                             // Je crée une variable indiquant l'état
                                                    // de la trame en cours

    do{
        for (i=0; i < 21; i++) {                    // On veut recopier 21 caractères
            trame[i] = fgetc(file_pf);              // On copie le caractère récupéré dans le buffer

            if(trame[i] == EOF){                    // Si le caractère est EOF on passe validTrame à 1
                *file_state = EOF;
                validTrame = 1;
            }
            else if(trame[i] == 13){                // Si le caractère récupéré est un CR
                if(i == 20){                        // On vérifie s'il est en 20eme position du buffer
                    validTrame = 1;                 // Si c'est le cas on met validTrame à 1
                }
                else{
                    i = -1;                         // Sinon on relance jusqu'à obtention d'un CR
                }                                   // en mettant i à -1 (car incrémentation du for)
            }
        }

    }while (validTrame != 1);                       // On recommence jusqu'à obtenir une trame valide càd
                                                    //fin du fichier ou une trame valide

    if (*file_state != EOF) {                       // Si ce n'est pas la fin de fichier on lance le traitement

        char *acr = malloc(5 * sizeof(char));       // Je déclare 4 char* correspondant aux 4 valeurs
        char *dcr = malloc(5 * sizeof(char));       // différentes à récupérer
        char *acir = malloc(5 * sizeof(char));
        char *dcir = malloc(5 * sizeof(char));

        int count = 0;                              // J'initialise un compteur qui va nous permettre
                                                    // de sélectionner la chaine où je souhaite écrire
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

        myAbsorp.acir = strtof(acir, &endptr) - 2048;       // Il ne reste plus qu'à assigner les différentes
        myAbsorp.dcir = strtof(dcir, &endptr);              // valeurs à la structure myAbsorb en convertissant
        myAbsorp.acr = strtof(acr, &endptr) - 2048;         // les char* en float et en n'oubliant pas de centrer
        myAbsorp.dcr = strtof(dcr, &endptr);                // les signaux acr

        free(acir);                                         // Enfin, on désalloue l'espace mémoire occupé
        free(acr);                                          // par nos chaines de caractères
        free(dcr);
        free(dcir);

        return myAbsorp;                                    // On retourne notre structure absorp

    } else {

        myAbsorp.acir = 0;                                  // Si c'est la fin du fichier on assigne la valeur 0
        myAbsorp.dcir = 0;                                  // aux signaux
        myAbsorp.acr = 0;
        myAbsorp.dcr = 0;

        return myAbsorp;
    }
}

#include "affichage.h"

void affichage(oxy myOxy){
    if(access(".verrouData", F_OK) == 0){               // Avant de mettre à jour le fichier on vérifie qu'il n'est pas déjà en écriture
                int k = 2;                                        // Si le fichier existe => Ne rien faire
    }
    else{
        fopen(".verrouData", "a");   // Si le fichier n'existe on le crée avant d'écrire sur Data.txt
        FILE* data = fopen("Data.txt", "r+");           // On ouvre le fichier Data.txt
        fprintf(data, "%d\n",myOxy.spo2);               // On écrit sur la première ligne le taux de saturation de l'oxygène dans le sang
        fprintf(data, "%d",myOxy.pouls);                 // On écrit sur la deuxième ligne le rythme cardiaque
        fclose(data);                                   // On ferme le fichier quand on a terminé l'écriture
        remove(".verrouData");                             // On supprime le fichier .verrouData une fois qu'on a terminé
    }
}


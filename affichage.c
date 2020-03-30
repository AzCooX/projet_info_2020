#include "affichage.h"

void affichageTest(int a, int b){
    oxy test;
    test.pouls = a;
    test.spo2 = b;
    affichage(test);    // Regarder si les valeurs dans Data.txt ont bien changé
}

void affichage(oxy myOxy) {
    if (access(".verrouData", F_OK) == 0) {     // Avant de mettre à jour le fichier on vérifie qu'il n'est pas déjà en écriture

    } else {
        FILE* verrouData = fopen(".verrouData", "a");       // Si le fichier n'existe on le crée avant d'écrire sur Data.txt
        FILE* data = fopen("Data.txt", "w");                // On ouvre le fichier Data.txt
        fprintf(data, "%d\n%d", myOxy.spo2,myOxy.pouls);    // On écrit sur la première ligne le taux de saturation de l'oxygène dans le sang
                                                            //On écrit sur la deuxième ligne le rythme cardiaque

        fclose(data);           // On ferme le fichier quand on a terminé l'écriture
        fclose(verrouData);     // On ferme le fichier verrouData
        remove(".verrouData");  // On supprime le fichier .verrouData une fois qu'on a terminé
    }
}

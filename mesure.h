#include "define.h"
#include "fichiers.h"
typedef struct{
    float lastMaximumACR;       //permet de stocker le maximum d'ACR trouvé sur la période
    float lastMinimumACR;       //permet de stocker le minimum d'ACR trouvé sur la période
    float lastMaximumACIR;      //permet de stocker le maximum d'ACIR trouvé sur la période
    float lastMinimumACIR;      //permet de stocker le minimum d'ACIR trouvé sur la période
    unsigned int compteur;  //permet de compter le nombre de points trouvé sur une période
    float previousVal;
    int oldPouls[10];        //tableau permettant le calcul d'une moyenne de pouls
    unsigned int indexPouls;    //index permettant l'utilisation du tableau oldPouls
    int pouls;

}param_mesure;

param_mesure* init_mesure();
void fin_mesure(param_mesure* myMes);
int calculPouls(absorp myAbsorp,param_mesure* myMes);
int calculSpo2(absorp myAbsorp,param_mesure* myMes);
oxy mesure(absorp myAbsorp, param_mesure* myMes);
oxy mesureTest(char* filename);


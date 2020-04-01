#include "define.h"
#include "fichiers.h"
typedef struct{
    float lastMaximumACR;
    float lastMinimumACR;
    float lastMaximumACIR;
    float lastMinimumACIR;
    unsigned int compteur;
    float previousVal;
    int oldPouls[10];        //tableau permettant le calcul d'une moyenne de pouls
    int indexPouls;
    int pouls;
    int spo2;

}param_mesure;

param_mesure* init_mesure();
void fin_mesure(param_mesure* myMes);
oxy mesure(absorp myAbsorp, param_mesure* myMes);
oxy mesureTest(char* filename);


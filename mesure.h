#include "define.h"
#include "fichiers.h"
typedef struct{
    float lastMaximum;
    float lastMinimum;
    float compteur;
    float previousVal;
}param_mesure;

param_mesure* init_mesure();
void fin_mesure(param_mesure* myMes);
oxy mesure(oxy myOxy,absorp myAbsorp, param_mesure* myMes);
oxy mesureTest(char* filename);


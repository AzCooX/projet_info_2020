#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "affichage.h"
#include "iir.h"
#include "fir.h"
#include "mesure.h"
#include "integration.h"
int main() {


    //affichage(test);
    //iirTest("record1_fir.dat");
    //firTest("record1.dat");
    //mesureTest("record1_iir.dat");
    integrationTest("record1.dat");
    return 0;
}
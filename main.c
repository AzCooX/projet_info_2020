#include <stdio.h>
#include "define.h"
#include "affichage.h"

int main() {

    oxy test;
    test.pouls = 192;
    test.spo2 = 103;
    affichage(test);


    return 0;
}
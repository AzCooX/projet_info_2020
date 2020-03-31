#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "affichage.h"
#include "iir.h"
#include "fir.h"
#include "lecture.h"
int main() {

    if(lectureTest() == 1){
        printf("C'est gagné");
    }
    else{
        printf("c'est perdu");
    };
    return 0;
}
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>

struct linear_system{
    double** coeficientes;
    double** icognitas;
    int ordem;
};


typedef struct linear_system linear_system, *plinear_system;




#endif


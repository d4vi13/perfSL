#include "calc.h"

void partial_pivoting(plinear_system ls, int pivot){
    int i;
    double max_ptr, max, *aux;
    max = ls->coeficientes[pivot][pivot];
    max_ptr = ls->coeficientes[pivot]
    
    for(i = pivot + 1; i < ls->ordem; i++)
        if(max < ls->coeficientes[i][pivot]){
            max = ls->coeficientes[pivot][pivot];
            max_ptr = ls->coeficientes[pivot]
        }

    
    aux = ls->coeficientes[pivot];
    ls->coeficientes[pivot] = max_ptr;
    ls->coeficientes[i] = aux;

    return;
} 

}


/*
 * Should be able to tell the start colunm by the row 
 * */
void row_reduction(plinear_system ls, int start_row){
    partial_pivoting(sl, start_row);


}

void solve_ls_eg(plinear_system ls){
    for(int i = 0; i < ls->ordem-1; i++)
        row_reduction(ls, i);

    solve_triangular_ls(ls);
}


void solve_ls_eg(plinear_system ls){



}

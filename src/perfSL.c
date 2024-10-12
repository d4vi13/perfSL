#include "perfSL.h"

void read_matrix(double **matrix, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j <= size; j++){
            scanf("%lf", &matrix[i][j]);
        }
    }
}

void print_ls(plinear_system ls){
    for(int i = 0; i < ls->ordem; i++){
        for(int j = 0; j <= ls->ordem; j++)
            printf("%lf ", ls->coeficientes[i][j]);
        printf("\n");
    }
}

// TODO check mallocs 
int  malloc_matrices(plinear_system sl){
    sl-> coeficientes = malloc(sl->ordem * sizeof * sl->coeficientes);
    sl-> icognitas = malloc(sl->ordem * sizeof * sl->icognitas);

    for(int i = 0; i < sl->ordem; i++){
        sl-> coeficientes[i] = malloc((sl->ordem+1) * sizeof **sl->coeficientes);
        sl-> icognitas[i] = malloc(sl->ordem * sizeof **sl->icognitas);
    }

    return 1;
}


int get_linear_system(plinear_system sl){
    scanf("%d", &sl->ordem);

    malloc_matrices(sl);

    read_matrix(sl->coeficientes, sl->ordem);

}


void solve_with_eg(plinear_system ls){
    
}

int main(){
    linear_system sl;
    get_linear_system(&sl);
    print_ls(&sl);
}


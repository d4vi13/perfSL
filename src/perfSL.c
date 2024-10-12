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
    sl-> icognitas = calloc((sl->ordem), sizeof * sl->icognitas);

    for(int i = 0; i < sl->ordem; i++){
        sl-> coeficientes[i] = malloc((sl->ordem+1) * sizeof **sl->coeficientes);
    }

    return 1;
}


int get_linear_system(plinear_system sl){
    scanf("%d", &sl->ordem);

    malloc_matrices(sl);

    read_matrix(sl->coeficientes, sl->ordem);

}

void retrosub(plinear_system ls){
    for(int i = ls->ordem-1; i >= 0; i--){
        ls->icognitas[i] = ls->coeficientes[i][ls->ordem];
        for(int j = i+1; j < ls->ordem; j++)
            /*
             *  Here theres the following problems:
             *  - When you subtract numbers it can create a lot of numeric imprecisions
             *  - Theres also the possibility of an overflow due to the multiplication
             * */
            ls->icognitas[i] -= ls->coeficientes[i][j] * ls->icognitas[j];
        // Heres theres the possibility of an division by zero
        ls->icognitas[i] /= ls->coeficientes[i][i];
    }  
}

void partial_pivoting(plinear_system ls, int i){
    int maxline_index = i; 
    double max, *aux;
    max = ls->coeficientes[i][i];
    for(int j = i; j < ls->ordem; j++){
        if(ls->coeficientes[j][i] > max){
            max = ls->coeficientes[j][i];
            maxline_index = j;
        }
    }
    
    aux = ls->coeficientes[i];
    ls->coeficientes[i] = ls->coeficientes[maxline_index];
    ls->coeficientes[maxline_index] = aux; 
    
}


void gaussian_elimination(plinear_system ls){
    double m;
    for(int i = 0; i < ls->ordem-1; i++){
        partial_pivoting(ls, i);
        for(int j = i+1; j < ls->ordem; j++){
            /*
             * notice that without the partial pivoting
             * we may have a lot of errors, because if the pivot line
             * has a small value, when we calculate m, we end up with a big m,
             * and in floating point representation big numbers have a 
             * very low precision, so when we do the partial pivoting, we
             * end up with a smaller m, resulting in a more precise result
             * */
            m = ls->coeficientes[j][i]/ls->coeficientes[i][i];
            ls->coeficientes[j][i] = 0.0;
            for(int k = i+1; k <= ls->ordem; k++)
                ls->coeficientes[j][k] -= ls->coeficientes[i][k]*m; 
        }
    } 
}

double sum(plinear_system ls, int i){
    double total = ls->coeficientes[i][ls->ordem];
    for(int j = 0; j < i; j++)
        total -= ls->icognitas[j]*ls->coeficientes[i][j]; 
    for(int j = i+1; j < ls->ordem; j++)
        total -= ls->icognitas[j]*ls->coeficientes[i][j]; 
    total /= ls->coeficientes[i][i];
    
    printf("total: %.15e\n",total);
    return total;
}

double max_error(plinear_system ls, double *x){
    double prev, max = fabs(ls->icognitas[0] - x[0]);
    for(int i = 0; i < ls->ordem; i++){
       prev = fabs(ls->icognitas[i] - x[i]);
       if (prev < max)
          max = prev; 
    }
    return max;
}

void gauss_seidel(plinear_system ls){
    double* x = calloc(ls->ordem, sizeof * x);
   
    do{ 
        memcpy(x, ls->icognitas, ls->ordem*sizeof*x);
        for(int i = 0; i < ls->ordem; i++){
            ls->icognitas[i] = sum(ls, i);
            printf("ic: %.15e\n", ls->icognitas[i]);
        }
    }while(max_error(ls, x) > 0.0001);
}


int main(){
    linear_system sl;
    get_linear_system(&sl);
    //gaussian_elimination(&sl);
    //retrosub(&sl);
    gauss_seidel(&sl);
    for (int i = 0; i < sl.ordem; i++)
        printf("%.15e ", sl.icognitas[i]);
    printf("\n"); 
    print_ls(&sl);
}


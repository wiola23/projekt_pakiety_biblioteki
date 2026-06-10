#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif
void swap_rows(double* A, int n, int row1, int row2);
int lu(double* A, int* P, int n){
    for(int p=0; p<n;++p){
        P[p]=p;
    }
    for(int k=0;k<n;++k){
    int max_row;
    max_row=k;
    for(int i=k+1; i<n;++i){
        
        if (fabs(A[i+k*n])>fabs(A[max_row + k*n])){
            max_row=i;
        }
    }

    if (fabs(A[max_row+ k*n])< 1e-13){
        return -1;
    }

    if (max_row != k){
    swap_rows(A,n,k,max_row);
    int temp = P[k];
    P[k]= P[max_row];
    P[max_row]=temp;
    }
    #pragma omp parallel for
    for(int w=k+1;w<n;++w){
        A[w+k*n] = A[w+k*n]/A[k+k*n];
        for (int j=k+1;j<n;++j){
            A[w+j*n]=A[w+j*n]- (A[w+k*n]*A[k+j*n]);
        }
    }
}
return 0;


}
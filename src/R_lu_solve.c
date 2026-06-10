#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>


extern void swap_rows(double* A,int n, int row1, int row2);
extern int lu(double* A, int* P, int n);
extern void lu_solve(const double* A, const int* P,const double* b, double* x, int n);

SEXP R_lu_solve(SEXP RA, SEXP Rb){

    if(!Rf_isMatrix(RA)||!Rf_isReal(RA)){
     
        Rf_error("A nie jest macierzą liczb rzeczywistych");
    }
    if(!Rf_isReal(Rb)){
      
        Rf_error("b nie jest wektorem liczb rzeczywistych");
    }
    
    int n= Rf_nrows(RA);
    if(n==0){
     
        Rf_error("Macierz A nie może mieć jednego z wymairów 0");
    }
    if(Rf_ncols(RA)!=n){
        
        Rf_error("Macierz A musi być kwadratowa");
    }
    if (XLENGTH(Rb) != n ){
        
        Rf_error("Wymiary macierzy A u wektora b muszą się zgadzać");
    }
    double* A_ptr = REAL(RA);
    for(int i=0;i<n*n;i++){
        if(ISNA(A_ptr[i]) || A_ptr[i]!=A_ptr[i]){
         
            Rf_error("Macierz A zawiera braki danych");
        }
    }
    double* b_ptr = REAL(Rb);
        for(int i=0;i<n;i++){
        if(ISNA(b_ptr[i]) || b_ptr[i]!=b_ptr[i]){
          
            Rf_error("Wektor b zawiera braki danych");
        }
    }
    SEXP Rx = PROTECT(Rf_allocVector(REALSXP,n));
    double* x_ptr = REAL(Rx);
    int* P = R_Calloc(n,int);

    int flag = lu(A_ptr, P,n);
    if(flag ==-1){
        R_Free(P);
        UNPROTECT(1);
        Rf_error("Wyznacznik zerowy");
    }

    lu_solve(A_ptr, P, b_ptr, x_ptr, n);
        R_Free(P);
        UNPROTECT(1);

    return Rx;
}
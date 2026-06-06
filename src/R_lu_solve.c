#include <R.h>
#include <Rinternals.h>

extern void swap_rows(double* A,int n, int row1, int row2);
extern int lu(double* A, int* P, int n);
extern void lu_solve(const double* A, const int* P,const double* b, double* x, int n);

SEXP R_lu_solve(SEXP RA, SEXP Rb){
    PROTECT(RA);
    PROTECT(Rb);
    if(!Rf_isMatrix(RA)||!Rf_isReal(RA)){
        UNPROTECT(2);
        error("A nie jest macierzą liczb rzeczywistych");
    }
    if(!Rf_isReal(Rb)){
        UNPROTECT(2);
        error("b nie jest wektorem liczb rzeczywistych");
    }
    
    int n= Rf_nrows(RA);
    if(n==0){
        UNPROTECT(2);
        error("Macierz A nie może mieć jednego z wymairów 0");
    }
    if(Rf_ncols(RA)!=n){
        UNPROTECT(2);
        error("Macierz A musi być kwadratowa");
    }
    if (XLENGTH(Rb) != n ){
        UNPROTECT(2);
        error("Wymiary macierzy A u wektora b muszą się zgadzać");
    }
    double* A_ptr = REAL(RA);
    for(int i=0;i<n*n;i++){
        if(ISNA(A_ptr[i]) || A_ptr[i]!=A_ptr[i]){
            UNPROTECT(2);
            error("Macierz A zawiera braki danych");
        }
    }
    double* b_ptr = REAL(Rb);
        for(int i=0;i<n;i++){
        if(ISNA(b_ptr[i]) || b_ptr[i]!=b_ptr[i]){
            UNPROTECT(2);
            error("Wektor b zawiera braki danych");
        }
    }
    SEXP Rx = PROTECT(Rf_allocVector(REALSXP,n));
    double* x_ptr = REAL(Rx);
    int* P = Calloc(n,int);

    int flag = lu(A_ptr, P,n);
    if(flag ==1){
        Free(P);
        UNPROTECT(3);
        error("Wyznacznik zerowy");
    }

    lu_solve(A_ptr, P, b_ptr, x_ptr, n);
        Free(P);
        UNPROTECT(3);

    return Rx;
}
#define R_NO_REMAP
#include <math.h>
#include <stdlib.h>
#include <R.h>
#include <Rinternals.h>
#include <omp.h>

SEXP R_itr_solve(SEXP r_A, SEXP r_b, SEXP r_x0, SEXP r_max_iter, SEXP r_d1, SEXP r_d2, SEXP r_method){

 if(!Rf_isMatrix(r_A) || !Rf_isReal(r_A)){
        Rf_error("A nie jest macierzą liczb rzeczywistych");
    }
    if(!Rf_isReal(r_b)){
        Rf_error("b nie jest wektorem liczb rzeczywistych");
    }
    if(!Rf_isReal(r_x0)){
        Rf_error("x0 nie jest wektorem liczb rzeczywistych");
    }

    int n = Rf_nrows(r_A);
    if(n == 0){
        Rf_error("Macierz A nie moze miec wymiaru 0");
    }
    if(Rf_ncols(r_A) != n){
        Rf_error("Macierz A musi byc kwadratowa");
    }
    if(XLENGTH(r_b) != n){
        Rf_error("Wymiary macierzy A i wektora b musza sie zgadzac");
    }
    if(XLENGTH(r_x0) != n){
        Rf_error("Wektor x0 musi miec te sama dlugosc co wektor b");
    }
    
    int max_iter=Rf_asInteger(r_max_iter);
    double d1 = Rf_asReal(r_d1);
    double d2 = Rf_asReal(r_d2);
    int method = Rf_asInteger(r_method);
    double* A =REAL(r_A);
    double* b = REAL(r_b);
    double* x0 = REAL(r_x0);

    for(int i=0; i<n; ++i){
        if(A[i+i*n]==0) Rf_error("0 na głównej diagonali");
    }
    SEXP r_x = PROTECT(Rf_allocVector(REALSXP, n));
    double *x = REAL(r_x);
          for(int i = 0; i < n; ++i) {
        x[i] = x0[i];
        }
    double* x_o = (double *)Calloc(n,double);

    double normd, norm;
    int iter;
    for(iter=0;iter<max_iter;++iter){
        for(int i = 0; i < n; ++i) {
        x_o[i] = x[i];
        }
        normd=0;
        norm=0;
        #pragma omp parallel for if(method == 0)
        for(int r=0; r<n;++r){
            double s=0;
            for(int c=0;c<n;++c){
                if(c==r) continue;
                if(method==0){
                    s+=A[r+c*n]*x_o[c];
                }
                else{
                    s+=A[r+c*n]*x[c];
                }
            }
            x[r]=(b[r]-s)/A[r+n*r];
        }
        #pragma omp parallel for reduction(+:normd, norm)
        for(int t=0;t<n;++t){
            normd+=pow((x[t]-x_o[t]),2);
            norm+=pow((x_o[t]),2);
        }
        if(sqrt(normd)<d2*sqrt(norm)+d1){
            iter++;
            break;}
    }
    Free(x_o);
    SEXP r_list = PROTECT(Rf_allocVector(VECSXP,2));
    SET_VECTOR_ELT(r_list, 0, r_x);
    SET_VECTOR_ELT(r_list, 1, PROTECT(Rf_ScalarInteger(iter)));
    UNPROTECT(3);
    return r_list;
}
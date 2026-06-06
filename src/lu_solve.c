void lu_solve(const double* A, const int* P, const double* b, double* x, int n){
    for (int i=0;i<n;++i){
        x[i]=b[P[i]];
    }

    for(int i=0;i<n;++i){
        for (int j=0;j<i;++j){
            x[i]=x[i]-A[i+j*n]*x[j];
        }
    }

    for(int i=n-1;i>=0;--i){
        for(int j=i+1;j<n;++j){
            x[i]=x[i]-A[i+j*n]*x[j];
        }
        x[i]=x[i]/A[i+i*n];
    }
}
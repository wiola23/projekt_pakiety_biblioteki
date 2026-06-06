void swap_rows(double* A, int n, int row1, int row2){
    if (row1==row2) return;
    double temp;
    for (int i=0; i < n; ++i){
        temp = A[row1 + i*n];
        A[row1 + i*n] = A[row2 + i*n];
        A[row2 + i*n] = temp;
    }
}
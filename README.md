# projektpakiety

## Description
The package contains solvers for systems of linear equations in the form of Ax = b, where A is a square matrix and b is a numeric vector. The package implements two primary approaches written in C: LU decomposition with partial pivoting, and iterative methods including both Jacobi and Gauss-Seidel algorithms. Iterative solvers utilize Gill's stopping criteria. Cores are parallelized using OpenMP.

## Build status
  <!-- badges: start -->
  [![R-CMD-check](https://github.com/wiola23/projekt_pakiety_biblioteki/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/wiola23/projekt_pakiety_biblioteki/actions/workflows/R-CMD-check.yaml)
  <!-- badges: end -->

## Installation
In order to install the project from GitHub:
remotes::install_github("wiola23/projekt_pakiety_biblioteki)

## License
The code is shared under MTI license.

## Usage & Examples
```r
library(projektpakiety)

A <- matrix(c(1, 1, 1, 0, 2, 5, 2, 5, -1), nrow = 3, byrow = TRUE)
b <- c(6, 19, 9)

wynik_lu <- lu_solve(A, b)
print(wynik_lu)
## [1] 1 2 3

A_iter <- matrix(c(4, 1, -1, 2, 7, 1, 1, -3, 12), nrow = 3, byrow = TRUE)
b_iter <- c(3, 19, 31)

wynik_jacobi <- iterative_solve(A_iter, b_iter, method = "jacobi")
print(wynik_jacobi$solution)
## [1] 1 2 3
print(wynik_jacobi$iterations)
## [1] 20

wynik_gs <- iterative_solve(A_iter, b_iter, method = "gauss-seidel")
print(wynik_gs$solution)
## [1] 1 2 3
print(wynik_gs$iterations)
## [1] 10

```
## References
Implemented algorithms are based on ones presented in "Notatki do wykładu Metody Numeryczne" and during lectures by dr inż. Iwona Wróbel

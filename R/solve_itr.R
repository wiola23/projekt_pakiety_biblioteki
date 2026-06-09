#' @title Solving linear equations using iterative methods
#' @description The function solves linear equations in form of Ax=b by using Jacobi or Gauss-Seidel methods (depending on choice) using Gill's stopping criteria, implemented in C language
#' @param A A square matrix of coefficents, numeric without any NA or NaN
#' @param b A numeric vector being the right side of the equation
#' @param x0 A numeric starting vector (default is a vector of zeros).
#' @param method A character string specifying the iterative method. Must be one of 
#'   \code{"jacobi"} (default) or \code{"gauss-seidel"}.
#' @param max_iter An integer specifying the maximum number of iterations allowed (default: 1000)
#' @param d1 A numeric value specifying the relative error tolerance (default: 1e-10)
#' @param d2 A numeric value specifying the absolute error tolerance (default: 1e-10)
#' @return A list containing two elements:
#' \item{solution}{A numeric vector representing the calculated solution x.}
#' \item{iterations}{An integer indicating the number of iterations actually performed.}
#' @useDynLib projektpakiety
#' 
#' @examples
#' A <- matrix(c(10, -1, 2, -1, 11, -1, 2, -1, 10), nrow = 3, byrow = TRUE)
#' b <- c(6, 25, -11)
#' # Start with default zeros:
#' iterative_solve(A, b, method = "jacobi")
#' # Start with a specific guess:
#' iterative_solve(A, b, x0 = c(1, 1, 1), method = "gauss-seidel")
#' @export 
#' 
iterative_solve <- function(A, b, x0 = rep(0, length(b)), method = c("jacobi", "gauss-seidel"), max_iter = 1000L, d1 = 1e-10, d2 = 1e-10){
    method <- match.arg(method)
    method_flag <- if (method == "jacobi") 0L else 1L
    storage.mode(A) <- "double"
    storage.mode(b) <- "double"
    storage.mode(x0) <- "double"
    if (length(x0) != length(b)) {
        stop("Wektor poczatkowy 'x0' musi miec taka sama dlugosc jak wektor 'b'.")
    }
    result <- .Call("R_itr_solve", A, b, x0,as.integer(max_iter), as.numeric(d1), as.numeric(d2), method_flag, PACKAGE = "projektpakiety")

    names(result) <- c("solution", "iterations")

    if (result$iterations >= max_iter) {
    warning(sprintf("Algorytm osiągnął limit iteracji (max_iter = %d) i mógł nie zbiec do końca!", max_iter))
  }
  return(result)
}
#' @title Solving linear equations using LU decomposition (Doolittle type)
#' @description The function solves linear equations in form of Ax=b by using LU
#' decomposition with partial pivoting (GEPP) all implemented in C language.
#' @param A A square matrix of coefficents, numeric without any NA or NaN
#' @param b A numeric vector 
#' @return A numeric vector representing a solution
#' @useDynLib projektpakiety
#' @export 
lu_solve<- function(A,b){

storage.mode(A) <- "double"
storage.mode(b) <- "double"
result <- .Call("R_lu_solve", A,b, PACKAGE = "projektpakiety")
return(result)
}
test_that("Metody iteracyjne", {
  macierz_A <- matrix(c(4, 1, -1, 2, 7, 1, 1, -3, 12), nrow = 3, byrow = TRUE)
  wektor_b <- c(3, 19, 31)
  prawidlowy_wynik <- c(1, 2, 3)
  
  wynik_jacobiego <- iterative_solve(macierz_A, wektor_b, method = "jacobi")
  expect_equal(wynik_jacobiego$solution, prawidlowy_wynik, tolerance = 1e-5)
  expect_true(wynik_jacobiego$iterations > 0)
  
  wynik_gaussa <- iterative_solve(macierz_A, wektor_b, method = "gauss-seidel")
  expect_equal(wynik_gaussa$solution, prawidlowy_wynik, tolerance = 1e-5)
  expect_true(wynik_gaussa$iterations > 0)
  
  dobry_start <- c(0.9, 1.9, 2.9)
  wynik_szybki <- iterative_solve(macierz_A, wektor_b, x0 = dobry_start, method = "gauss-seidel")
  expect_equal(wynik_szybki$solution, prawidlowy_wynik, tolerance = 1e-5)
  expect_true(wynik_szybki$iterations < wynik_gaussa$iterations)
  
  zly_wektor_startowy <- c(0, 0)
  expect_error(iterative_solve(macierz_A, wektor_b, x0 = zly_wektor_startowy))
  
  macierz_z_zerem <- matrix(c(0, 1, 1, 0), nrow = 2)
  wektor_testowy <- c(1, 1)
  expect_error(iterative_solve(macierz_z_zerem, wektor_testowy))
})
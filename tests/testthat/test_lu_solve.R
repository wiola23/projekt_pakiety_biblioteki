test_that("Metoda LU", {
  macierz_A <- matrix(c(1, 1, 1, 0, 2, 5, 2, 5, -1), nrow = 3, byrow = TRUE)
  wektor_b <- c(6, 19, 9)
  prawidlowy_wynik <- c(1, 2, 3)

  wynik_lu <- lu_solve(macierz_A, wektor_b)
  
  expect_equal(wynik_lu, prawidlowy_wynik, tolerance = 1e-5)

  macierz_osobliwa <- matrix(c(1, 2, 3, 2, 4, 6, 1, 1, 1), nrow = 3, byrow = TRUE)
  wektor_testowy <- c(1, 2, 3)
  
  expect_error(lu_solve(macierz_osobliwa, wektor_testowy))

  zly_wektor <- c(1, 2)
  expect_error(lu_solve(macierz_A, zly_wektor))
})
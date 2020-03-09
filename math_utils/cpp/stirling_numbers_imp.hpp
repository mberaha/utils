#ifndef UTILS_MATH_STIRLING_NUMBERS_IMP_HPP
#define UTILS_MATH_STIRLING_NUMBERS_IMP_HPP

#include "stirling_numbers.hpp"

template <class F>
stirlingmemoizer::stirlingmemoizer(F f) {
  maxN = maxM = 100;
  memoMatrix.resize(maxN + 1);
  memoMatrix[0].resize(1);
  memoMatrix[0][0] = 1;
  for (int n = 1; n <= maxN; n++) {
    memoMatrix[n].resize(n + 1);
    memoMatrix[n][0] = 0;
    for (int m = 1; m <= n; m++) {
      memoMatrix[n][m] = (n - 1) * memoMatrix[n - 1][m] + memoMatrix[n - 1][m - 1];
    }
  }
}

template <class F>
void stirlingmemoizer::addRows(F f, int newMaxN) {
  memoMatrix.resize(newMaxN + 1);
  for (int n = maxN; n <= newMaxN; n++) {
    memoMatrix[n].resize(n + 1);
    memoMatrix[n][0] = 0;
    for (int m = 1; m <= n; m++) {
      memoMatrix[n][m] = (n - 1) * f(n - 1, m) + f(n - 1, m - 1);
    }
  }
  maxN = newMaxN;
}

template <class F>
const unsigned long int& stirlingmemoizer::operator()(F f, int n, int m) {
    if (n > maxN)
     addRows(f, n);
    return memoMatrix[n][m];
}



#endif  // UTILS_MATH_STIRLING_NUMBERS_HPP

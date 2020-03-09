#ifndef UTILS_MATH_STIRLING_NUMBERS_HPP
#define UTILS_MATH_STIRLING_NUMBERS_HPP

#include <vector>
#include <iostream>
// UTILITY FOR COMPUTING EFFICIENTLY STIRLING NUMBERS OF THE FIRST KIND

/*
 * Memoizer specific to the stirling numbers: instead of using
 * a map, employs a lower triangular matrix to gain efficiency.
 */
class stirlingmemoizer {
 private:
   std::vector<std::vector<unsigned long int>> memoMatrix;
   int maxN;
   int maxM;

 public:
   template <class F>
   stirlingmemoizer(F f);

   template <class F>
   void addRows(F f, int newMaxN);

   template <class F>
   const unsigned long int& operator()(F f, int n, int m);

};

unsigned long int stirling(int n, int m);

namespace {
  unsigned long int stirling_(int n, int m) {
    if (((n == 0) & (m == 0)) ||( (n == 1) & (m == 1)))
      return 1;
    else if ((n > 0) & (m == 0))
      return 0;
    else if (m > n)
      return 0;
    else
      return stirling(n-1, m-1) + (n-1) * stirling(n-1, m);
  }
}

unsigned long int stirling(int n, int m);


#include "stirling_numbers_imp.hpp"

#endif  // UTILS_MATH_STIRLING_NUMBERS_HPP

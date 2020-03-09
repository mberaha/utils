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
   stirlingmemoizer();

   void addRows(int newMaxN);

   const unsigned long int& operator()(int n, int m);

   void print() {
     for (int i = 0; i < maxN; i++) {
           for (int j=0; j < i+1; j++) {
               std::cout << memoMatrix[i][j] << ", ";
           }
           std::cout << std::endl;
       }
   }

};

unsigned long int stirling(int n, int m);

namespace {
  unsigned long int stirling_(int n, int m) {
    unsigned long int out;
    if (((n == 0) & (m == 0)) ||( (n == 1) & (m == 1))) {
      out = 1;
    }
    else if ((n > 0) & (m == 0)) {
      out = 0;
    }
    else if (m > n) {
      out = 0;
    }
    else
      out = stirling(n-1, m-1) + (n-1) * stirling(n-1, m);
    
    return out;
  }
}

unsigned long int stirling(int n, int m);


#include "stirling_numbers_imp.hpp"

#endif  // UTILS_MATH_STIRLING_NUMBERS_HPP

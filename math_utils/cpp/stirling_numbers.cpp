#include "stirling_numbers.hpp"

unsigned long int stirling(int n, int m) {
  static stirlingmemoizer memo(stirling_);
  return memo(stirling_, n, m);
}

#include "stirling_numbers.hpp"

unsigned long int stirling(int n, int m) {
  static stirlingmemoizer memo;
  return memo(n, m);
}

stirlingmemoizer::stirlingmemoizer()
{
  maxN = maxM = 0;
  memoMatrix.resize(maxN + 1);
  memoMatrix[0].resize(1);
  memoMatrix[0][0] = 1;
}

void stirlingmemoizer::addRows(int newMaxN)
{
  memoMatrix.resize(newMaxN + 1);
  for (int n = maxN; n <= newMaxN; n++)
  {
    memoMatrix[n].resize(n + 1);
    memoMatrix[n][0] = 0;
    for (int m = 1; m < n; m++)
    {
      memoMatrix[n][m] = (n - 1) * memoMatrix[n - 1][m] + memoMatrix[n - 1][m - 1];
    }
    memoMatrix[n][n] = 1;
  }
  maxN = newMaxN;
}

const unsigned long int &stirlingmemoizer::operator()(int n, int m)
{
  if (n > maxN)
    addRows(n);
  return memoMatrix[n][m];
}
#include <iostream>
#include <math.h>

int numFactors(int n)
{
  int result = 0;
  const int stop = sqrt(n);
  for (int i = 1; i <= stop; ++i) {
    if (n%i == 0) {
      result += (n/i == i ? 1 : 2);
    }
  }
  return result;
}

int main() {
  int triangleNum = 1;
  for (int i = 2; numFactors(triangleNum) <= 500; ++i) {
    triangleNum += i;
  }
  std::cout << triangleNum << "\n";
}

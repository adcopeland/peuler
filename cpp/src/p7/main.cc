#include <iostream>
#include "utils.h"

int main() {
  int primeIdx = 0;
  int current = 1;

  while (primeIdx < 10001) {
    ++current;
    if (isPrime(current)) {
      ++primeIdx;
    }
  }

  std::cout << current << "\n";
}

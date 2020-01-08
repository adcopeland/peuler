#include <iostream>

bool isPrime(int n) {
  const int stop = n >> 1;
  for (int i = 2; i <= stop; ++i) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

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

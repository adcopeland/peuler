// sum primes below 2 million

#include <iostream>
#include <cstdint>
#include "utils.h"

int main() {
  uint64_t sum = 0;
  for (int i = 2; i < 2000000; ++i) {
    if (isPrime(i)) {
      sum += i;
    }
  }
  std::cout << sum << "\n";
}

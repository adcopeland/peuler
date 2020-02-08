#include "BigInt.h"
#include <iostream>

int main() {
  BigInt facResult("1");
  const BigInt end("101");
  const BigInt increment("1");
  for (BigInt current("1"); current < end; current.Add(increment)) {
    facResult.Mul(current);
  }

  int sum = 0;
  for (const auto c : facResult.String()) {
    sum += static_cast<int>(c - '0');
  }

  std::cout << sum << "\n";
}

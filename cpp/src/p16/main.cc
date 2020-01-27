#include <iostream>
#include "BigInt.h"

// Reusing logic from p13.
int main() {
	// start at 2^0, loop 1000 times
  BigInt current("1");
  for (int i = 0;i < 1000; ++i) {
		// Add the number to itself to double it. This takes 2^n => 2^(n+1)
    current.Add(current);
  }

  int sum = 0;
  const std::string str = current.String();
  for (const auto c : str) {
    sum += (c - '0');
  }

  std::cout << sum << "\n";
}

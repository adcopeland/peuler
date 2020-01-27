#include <iostream>
#include <vector>

std::vector<uint64_t> getFactors(uint64_t n) {
  std::vector<uint64_t> result;
  for (uint64_t i = 2u; i < n; ++i) {
    if ((n%i) == 0) {
      result.push_back(i);
      n /= i;
      i = 1;
    }
  }

  if (n != 1) {
    result.push_back(n);
  }
  return result;
}

// Largest prime factor of 600851475143
int main() {
  const auto factors = getFactors(600851475143u);
  uint64_t max = 0u;
  for (const auto& factor : factors) {
    if (factor > max) {
      max = factor;
    }
  }
  std::cout << max << "\n";
}

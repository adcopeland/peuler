#include <iostream>
#include <vector>
#include <stdlib.h>

bool isPalindrome(int n)
{
  const std::string s = std::to_string(n);
  const size_t stop = s.size() >> 1;
  for (size_t i = 0; i < stop; ++i) {
    if (s[i] != s[s.size()-i-1]) {
      return false;
    }
  }
  return true;
}

int main() {
  std::vector<int> palindromes;
  for (int x = 100; x <= 999; ++x) {
    for (int y = 100; y <= 999; ++y) {
      const int product = x*y;
      if (isPalindrome(product)) {
        palindromes.push_back(product);
      }
    }
  }

  int max = 0;
  for (const int x : palindromes) {
    max = (x > max ? x : max);
  }

  std::cout << max << "\n";
}

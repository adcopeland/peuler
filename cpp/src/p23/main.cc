#include <iostream>
#include <vector>

bool isAbundant(const int n) {
  // skip 1, count it in the sum, because the value itself isn't a divisor but 1 is.
  // This way, for all other divisors we can catch both at the same time (2 and n/2 for example)
  // and stop earlier
  int sum = 1;
  int stop = n-1;
  for (int i = 2; i < stop; ++i) {
    if (n % i == 0) {
      sum += i;
      stop = n/i;
      sum += stop != i ? stop : 0;
    }
  }
  return (sum > n);
}

bool isSumOfTwoAbundants(int n, const std::vector<int>& abundantNumbers) {
  const int abundant_size = static_cast<int>(abundantNumbers.size());
  for (int i = 0; i < abundant_size; ++i) {
    const int smallestSumForI = abundantNumbers[i] + abundantNumbers[i];
    if (smallestSumForI > n) {
      break;
    }

    for (int j = i; j < abundant_size; ++j) {
      const int sum = abundantNumbers[i] + abundantNumbers[j];
      if (sum == n) {
        return true;
      }

      if (sum > n) {
        break;
      }
    }
  }

  return false;
}

int main() {
  int sum = 0;
  std::vector<int> abundantNumbers;
  for (int i = 1; i <= 28123; ++i) {
    if (isAbundant(i)) {
      abundantNumbers.emplace_back(i);
    }

    if (!isSumOfTwoAbundants(i, abundantNumbers)) {
      sum += i;
    }
  }

  std::cout << sum << "\n";
}

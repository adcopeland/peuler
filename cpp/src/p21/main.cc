#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Implement problem 21 (find the sum of all amicable numbers below 10000)
int main() {
  std::unordered_map<int, int> numToSum;

  // Build up all the sums
  for (int i = 1; i < 10000; ++i) {
    int sum = 0;
    int stop = i/2;
    for (int j = 1; j <= stop; ++j) {
      if (i % j == 0) {
        sum += j;
      }
    }
    numToSum[i] = sum;
  }

  // Figure out which numbers are amicable
  std::unordered_set<int> amicables;
  for (const auto& [num, sum] : numToSum) {
    if (num != sum && numToSum[sum] == num) {
      amicables.emplace(num);
      amicables.emplace(sum);
    }
  }

  // sum the amicable numbers
  int sum = 0;
  for (const auto amicable : amicables) {
    sum += amicable;
  }

  std::cout << sum << "\n";
}

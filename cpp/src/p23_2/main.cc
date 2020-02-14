#include <algorithm>
#include <iostream>
#include <numeric>
#include <thread>
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

// Merges toMerge into a flattened result while maintaining order. Only works if -1 is not a valid element in the toMerge vectors.
std::vector<int> merge(const std::vector<std::vector<int>>& toMerge) {
  std::vector<int> result;
  for (const auto& vec : toMerge) {
    for (const int val : vec) {
      result.emplace_back(val);
    }
  }

  std::sort(result.begin(), result.end());
  return result;
}

int main() {
  const int numThreads = std::thread::hardware_concurrency();

  // Phase 1: stride through the data and generate per-thead abundant numbers
  std::vector<std::thread> threads;
  std::vector<std::vector<int>> abundantNumbersPerThread(numThreads);
  for (int threadNum = 0; threadNum < numThreads; ++threadNum) {
    threads.emplace_back([&abundantNumbersPerThread, numThreads, threadNum]() {
      for (int i = 1+threadNum; i <= 28123; i += numThreads) {
        if (isAbundant(i)) {
          abundantNumbersPerThread[threadNum].emplace_back(i);
        }
      }
    });
  }
  for (auto& t : threads) {
    t.join();
  }
  threads.clear();

  // Phase 2: merge the per-thread data together
  const std::vector<int> abundantNumbers = merge(abundantNumbersPerThread);

  // Phase 3: split back out again and calculate the per-thread sums
  std::vector<int> perThreadSums(numThreads, 0);
  for (int threadNum = 0; threadNum < numThreads; ++threadNum) {
    threads.emplace_back([&abundantNumbers, &perThreadSums, numThreads, threadNum]() {
      for (int i = 1+threadNum; i <= 28123; i += numThreads) {
        if (!isSumOfTwoAbundants(i, abundantNumbers)) {
          perThreadSums[threadNum] += i;
        }
      }
    });
  }
  for (auto& t : threads) {
    t.join();
  }
  threads.clear();

  // Phase 4: "merge" the per-thread sums
  const int sum = std::accumulate(perThreadSums.begin(), perThreadSums.end(), 0);
  std::cout << sum << "\n";
}

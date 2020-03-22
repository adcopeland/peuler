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

int main() {
  const int numThreads = std::thread::hardware_concurrency();

  // abundant numbers for thread data. Each threads puts results here.
  // numbers that are abundant get 1, others get 0
  std::vector<int> abundantNumbers(28123);

  // Phase 1: stride through the data and generate per-thead abundant numbers
  std::vector<std::thread> threads;
  for (int threadNum = 0; threadNum < numThreads; ++threadNum) {
    threads.emplace_back([&abundantNumbers, numThreads, threadNum]() {
      for (int i = 1+threadNum; i <= 28123; i += numThreads) {
        abundantNumbers[i-1] = isAbundant(i);
      }
    });
  }
  for (auto& t : threads) {
    t.join();
  }
  threads.clear();

  // Phase 2: Go back through and update the numbers "correctly".
  // Even though it doesn't take much space, we'll do it in-place
  int nextIndex = 0;
  for (int i = 0; i < 28123; ++i) {
    if (abundantNumbers[i] > 0) {
      abundantNumbers[nextIndex] = i+1;
      ++nextIndex;
    }
  }
  abundantNumbers.resize(nextIndex);

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

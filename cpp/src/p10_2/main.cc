// sum primes below 2 million

#include <cstdint>
#include <iostream>
#include <thread>
#include <vector>
#include "utils.h"

static const int NUM_THREADS = std::thread::hardware_concurrency();

int main() {
  // setup
  std::vector<uint64_t> answers(NUM_THREADS, 0);

  // Run threads that handle a part of the problem
  std::vector<std::thread> threads;
  for (int id = 0; id < NUM_THREADS; ++id) {
    threads.emplace_back([id,&answers]() {
      uint64_t sum = 0;
      for (int i = 0+id; i < 2000000; i+=NUM_THREADS) {
        if (isPrime(i)) {
          sum += i;
        }
      }
      answers[id] = sum;
    });
  }

  // Wait for them to finish
  for (auto& t : threads) {
    t.join();
  }

  // Collect the answers and print
  uint64_t sum = 0;
  for (const auto v : answers) {
    sum += v;
  }

  std::cout << sum << "\n";
}

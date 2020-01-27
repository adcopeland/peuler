#include <iostream>

class FibonacciSequence {
  public:
    uint64_t Next() {
      const uint64_t temp = current;
      current = prev + current;
      prev = temp;
      return current;
    }

    uint64_t Current() const
      { return current; }

  private:
    uint64_t prev    = 1u;
    uint64_t current = 1u;
};

// sum even fibonacci terms <= 4 million
int main() {
  uint64_t total = 0u;
  FibonacciSequence seq;
  for (uint64_t n = seq.Current(); n <= 4000000u; n = seq.Next()) {
    if (n%2 == 0) {
      total += n;
    }
  }
  std::cout << total << "\n";
}

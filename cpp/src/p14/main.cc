#include <iostream>
#include <cstdint>

int next(uint32_t n) {
  // I thought this would be faster but it doesn't seem to matter.
  // Perhaps there's an optimization fixing it up.
  //return (n&1) ? (3*n+1) : (n>>1);
  return (n % 2 == 1)
            ? (3*n+1)
            : (n/2);
}

int seqLen(uint32_t n) {
  int seqLen = 0;
  while (n != 1) {
    seqLen++;
    n = next(n);
  }
  return seqLen;
}

int main() {
  int maxSeqLen = 0;
  int maxSeqLenNum = 0;
  for (uint32_t i = 1u; i < 1000000u; ++i) {
    const int l = seqLen(i);
    if (l > maxSeqLen) {
      maxSeqLen = l;
      maxSeqLenNum = i;
    }
  }
  std::cout << maxSeqLenNum << "\n";
}

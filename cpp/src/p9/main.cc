#include <iostream>

int findAnswer() {
  for (int a = 0; a < 998; ++a) {
    for (int b = a+1; b < 999; ++b) {
      for (int c = b+1; c < 1000; ++c) {
        if (a+b+c == 1000 && a*a + b*b == c*c) {
          return a*b*c;
        }
      }
    }
  }
  return 0;
}

int main() {
  std::cout << findAnswer() << "\n";
}

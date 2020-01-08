#include <iostream>

bool divisible_by_all(int n) {
  for (int i = 2; i <= 20; ++i) {
    if (n % i != 0) {
      return false;
    }
  }
  return true;
}

int main() {
  int n = 20;
  for(;;) {
    if (divisible_by_all(n)) {
      break;
    }
    n++;
  }

  std::cout << n << "\n";
}

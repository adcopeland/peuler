#include <iostream>
#include <algorithm>

int main() {
  char numbers[] = {'0','1','2', '3', '4', '5', '6', '7', '8', '9', '\0'};

  size_t i = 1;
  while (i < 1000000 && std::next_permutation(numbers, numbers+sizeof(numbers)-1)) {
    ++i;
  }

  std::cout << numbers << "\n";
}

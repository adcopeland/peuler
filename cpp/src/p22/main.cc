#include <fstream>
#include <iostream>
#include <set>

std::set<std::string> readNames() {
  std::ifstream ifs("../data/p022_names.txt");
  if (!ifs.good()) {
    std::cout << "Cannot read ../data/p022_names.txt\n";
    exit(1);
  }

  // The file is one line with names in all caps surrounded in quotes, split by commas.
  // "NAME1","NAME2",...
  std::set<std::string> names;
  std::string name;
  while (std::getline(ifs, name, ',')) {
    // Remove the quotes on either side of the name (first and last char)
    names.emplace(name.substr(1, name.size()-2));
  }

  return names;
}

int main() {
  unsigned int totalScore = 0;
  const std::set<std::string> names = readNames();
  unsigned int i = 0;
  for (const auto& name : names) {
    int wordScore = 0;
    for (auto c : name) {
      // Only works if names are all capital letters (they are). Add 1 since A is 1, not 0.
      wordScore += c - 'A' + 1;
    }
    ++i;
    totalScore += wordScore * i;
  }

  std::cout << totalScore << "\n";
}

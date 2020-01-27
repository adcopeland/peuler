#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string_view>

// used by lettersIn for numbers lower than 20
static constexpr std::string_view uniques[] = {
	"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
	"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen",
};

// used by lettersIn to determine the tens prefix.
// "zero" and "teens" are placeholders so num/10 resolves to the right index.
static constexpr std::string_view tens[] = {
	"zero", "teens", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety",
};

// Returns any non-space letters in the provided string
int lettersInPhrase(const std::string_view& phrase) {
  int sum = 0;
  for (const auto c : phrase) {
    sum += !isspace(c) ? 1 : 0;
  }
  return sum;
}

// Returns the number of letters in the english version of the number
int lettersIn(int num) {
	if (num >= 1000) {
		throw std::runtime_error("lettersIn only works below 1000");
	}

  std::string result;
	if (num >= 100) {
		const int numHundreds = num / 100;
    result.append(uniques[numHundreds]);
    result.append(" hundred ");
		num -= numHundreds * 100;
		if (num > 0) {
			result.append("and ");
		}
	}

	if (num >= 20) {
		const int numTens = num / 10;
    result.append(tens[numTens]);
    result += ' ';
		num -= numTens * 10;
	}

	if (num > 0) {
    result.append(uniques[num]);
	}

	return lettersInPhrase(result);
}

// sum the count of letters in all numbers from 1 to 1000
int main() {
  int sumLetters = 0;
  for (int i = 1; i < 1000; ++i) {
    sumLetters += lettersIn(i);
  }

  sumLetters += lettersInPhrase("one thousand");
  std::cout << sumLetters << "\n";
}

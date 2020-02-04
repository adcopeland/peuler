#include <iostream>

int main() {
	int sum = 0;
	int sum_of_squares = 0;
	for (int i = 1; i <= 100; ++i) {
		sum += i;
		sum_of_squares += i * i;
	}

	const int square_of_sum = sum * sum;
	std::cout << (square_of_sum - sum_of_squares) << "\n";
}

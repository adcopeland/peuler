package main

import "fmt"

func main() {
	sum := 0
	sum_of_squares := 0
	for i := 1; i <= 100; i++ {
		sum += i
		sum_of_squares += i * i
	}

	square_of_sum := sum * sum
	fmt.Println(square_of_sum - sum_of_squares)
}

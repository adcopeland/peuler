package main

import "fmt"

// Largest prime factor of 600851475143
func main() {
	factors := getFactors(600851475143)

	var max uint64 = 0
	for _, factor := range factors {
		if factor > max {
			max = factor
		}
	}

	fmt.Println(max)
}

func getFactors(n uint64) []uint64 {
	result := make([]uint64, 0)

	for i := uint64(2); i < n; i++ {
		if n%i == 0 {
			result = append(result, i)
			n /= i
			i = 1
		}
	}

	if n != 1 {
		result = append(result, n)
	}

	return result
}

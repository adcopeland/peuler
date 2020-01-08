package main

import "fmt"

func main() {
	primeIdx := 0
	current := 1

	for primeIdx < 10001 {
		current++
		if isPrime(current) {
			primeIdx++
		}
	}

	fmt.Println(current)
}

func isPrime(n int) bool {
	stop := n / 2
	for i := 2; i <= stop; i++ {
		if n%i == 0 {
			return false
		}
	}
	return true
}

package main

import (
	"fmt"
	"math/big"
)

// sum digits of 2^1000
func main() {
	// start at 2^0, loop 1000 times
	current := big.NewInt(1)
	for i := 0; i < 1000; i++ {
		// Add the number to itself to double it. This takes 2^n => 2^(n+1)
		current.Add(current, current)
	}

	// now current is 2^1000, get the digits and sum them.
	str := current.String()
	digitSum := 0
	for _, c := range str {
		digitSum += int(c - '0')
	}

	fmt.Println(digitSum)
}

package main

import (
	"fmt"
	"strconv"
)

// largest palindrome of product of 2 3-digit numbers.
// Note that order doesn't matter (101x102 == 102x101)
func main() {
	palindromes := make([]int, 0)
	for x := 100; x <= 999; x++ {
		for y := 100; y <= 999; y++ {
			product := x * y
			if isPalindrome(product) {
				palindromes = append(palindromes, product)
			}
		}
	}

	max := 0
	for _, p := range palindromes {
		if p > max {
			max = p
		}
	}

	fmt.Println(max)
}

func isPalindrome(n int) bool {
	str := strconv.Itoa(n)
	stop := len(str) / 2
	for i, _ := range str {
		if i > stop {
			break
		}
		if str[i] != str[len(str)-i-1] {
			return false
		}
	}
	return true
}

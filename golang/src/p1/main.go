package main

import "fmt"

// Problem 1: Sum numbers below 1000 that are multiples of 3 or 5
func main() {
	total := 0
	for i := 0; i < 1000; i++ {
		if i%3 == 0 || i%5 == 0 {
			total += i
		}
	}
	fmt.Println(total)
}

package main

import "fmt"
import "acommon"

func main() {
	primeIdx := 0
	current := 1

	for primeIdx < 10001 {
		current++
		if acommon.IsPrime(current) {
			primeIdx++
		}
	}

	fmt.Println(current)
}

package main

import (
	"fmt"
	"math"
)

func main() {
	triangleNum := 1
	for i := 2; numFactors(triangleNum) <= 500; i++ {
		triangleNum += i
	}

	fmt.Println(triangleNum)
}

func numFactors(n int) int {
	sqrtN := int(math.Sqrt(float64(n)))
	result := 0
	for i := 1; i <= sqrtN; i++ {
		if n%i == 0 {
			if n/i == i {
				result += 1
			} else {
				result += 2
			}
		}
	}
	return result
}

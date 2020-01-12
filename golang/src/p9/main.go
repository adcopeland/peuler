// a < b < c
// a^2 + b^2 = c^2
// find a*b*c when a+b+c == 1000
// * since a < b < c and a+b+c == 1000, we know the worst case max value is 999 (0, 1, 999)

package main

import "fmt"

func main() {
	fmt.Println(findAnswer())
}

// wrap in findAnswer since it's easier to return out of nested loops than break
func findAnswer() int {
	for a := 0; a < 998; a++ {
		for b := a + 1; b < 999; b++ {
			for c := b + 1; c < 1000; c++ {
				if a+b+c == 1000 && a*a+b*b == c*c {
					return a * b * c
				}
			}
		}
	}
	return 0
}

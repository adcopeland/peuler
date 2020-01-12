package main

import "fmt"
import "acommon"

func main() {
	sum := uint64(2)

	for i := 3; i < 2000000; i += 2 {
		if acommon.IsPrime(i) {
			sum += uint64(i)
		}
	}

	fmt.Println(sum)
}

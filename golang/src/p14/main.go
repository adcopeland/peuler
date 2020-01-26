package main

import "fmt"

// n ->  n/2 (n is even)
// n -> 3n+1 (n is odd)
// sequence to 1 (e.g. 13, 40, 20, 10, 5, 16, 8, 4, 2, 1)
// Which starting number below 1 million has the most terms (10 above)
func main() {
	maxSeqLen := 0
	maxSeqLenNum := 0
	for i := 1; i < 1000000; i++ {
		l := seqLen(i)
		if l > maxSeqLen {
			maxSeqLen = l
			maxSeqLenNum = i
		}
	}

	fmt.Println(maxSeqLenNum)
}

func seqLen(n int) int {
	seqLen := 0
	for n != 1 {
		seqLen++
		n = next(n)
	}
	return seqLen
}

func next(n int) int {
	// in cpp and rust bit math vs mod+divide didn't seem to matter,
	// but in golang it does seem to make a difference.
	if n&1 == 1 {
		return 3*n + 1
	}
	return n >> 1

	//if n%2 == 1 {
	//	return 3*n + 1
	//}
	//return n / 2
}

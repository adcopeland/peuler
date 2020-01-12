package main

import (
	"acommon"
	"fmt"
	"runtime"
	"sync"
)

func main() {
	// setup
	NumParallel := runtime.NumCPU()
	answers := make([]uint64, NumParallel)

	var wg sync.WaitGroup
	wg.Add(NumParallel)

	// Run the threads to divide up the work and find the sum
	for id := 0; id < NumParallel; id++ {
		go func(id int) {
			sum := uint64(0)
			for i := 1 + id; i < 2000000; i += NumParallel {
				if acommon.IsPrime(i) {
					sum += uint64(i)
				}
			}
			answers[id] = sum
			wg.Done()
		}(id)
	}

	// When they're all done, add them all up for the final sum
	wg.Wait()
	sum := uint64(0)
	for _, v := range answers {
		sum += v
	}

	fmt.Println(sum)
}

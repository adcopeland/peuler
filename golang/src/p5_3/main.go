// 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
// What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

package main

import (
	"fmt"
	"runtime"
	"sync"
	"sync/atomic"
)

func main() {
	// We'll run 8 threads that run in strides and have a place to store their result,
	// then when at least one is done take the smallest result

	// Set up
	NumParallel := runtime.NumCPU()
	answers := make([]int, NumParallel)
	var done int32 = 0
	var wg sync.WaitGroup
	wg.Add(NumParallel)

	// Run the threads
	for i := 0; i < NumParallel; i++ {
		go func(id int) {
			for n := 20 + id; atomic.LoadInt32(&done) == 0; n += NumParallel {
				if divisibleByAll(n) {
					answers[id] = n
					atomic.StoreInt32(&done, 1)
					break
				}
			}
			wg.Done()
		}(i)
	}

	// Wait for the threads and find the smallest answer
	wg.Wait()

	answer := 1 << 31
	for _, v := range answers {
		// Skip answers that weren't found (0) and get the smallest found answer
		if v != 0 && v < answer {
			answer = v
		}
	}

	// Then print
	fmt.Println(answer)
}

func divisibleByAll(n int) bool {
	for i := 2; i <= 20; i++ {
		if n%i != 0 {
			return false
		}
	}

	return true
}

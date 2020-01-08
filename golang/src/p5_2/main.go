// 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
// What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

package main

import "fmt"
import "sync"

const NumParallel = 8

func main() {
	var wg sync.WaitGroup

	answerChannel := make(chan int)
	doneChannel := make(chan bool)

	workerFunc := func(id int) {
		done := false
		for n := 20 + id; !done; n += NumParallel {
			select {

			// Check if we are done due to doneChannel
			case <-doneChannel:
				done = true

				// Do normal loop work
			default:
				if divisibleByAll(n) {
					answerChannel <- n
					done = true
				}
			}
		}
		wg.Done()
	}

	// start workers. Technically there's a race here since the first one to get to the "smallest" number
	// wins and will be considered the smallest, this assumes they progress at a similar rate and there's some
	// leeway until the next number divisible by all the numbers from 1 to 20
	wg.Add(NumParallel)
	for i := 0; i < NumParallel; i++ {
		go workerFunc(i)
	}

	answer := <-answerChannel
	for i := 0; i < NumParallel-1; i++ {
		doneChannel <- true
	}

	wg.Wait()
	close(doneChannel)
	close(answerChannel)

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

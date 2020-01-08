package main

import "fmt"

// Problem 2: Sum the even fibonacci terms that do not exceed 4 million
func main() {
	var total uint64 = 0
	seq := NewFibonacciSequence()

	for n := seq.Current(); n <= 4000000; n = seq.Next() {
		if n%2 == 0 {
			total += n
		}
	}

	fmt.Println(total)
}

// Holds state for a "sequence" of fibonacci numbers, where the sequence starts "1, 2, 3, 5, ..."
type FibonacciSequence struct {
	prev uint64
	curr uint64
}

// Create a new fibonacci sequence
func NewFibonacciSequence() *FibonacciSequence {
	return &FibonacciSequence{
		prev: 1,
		curr: 1,
	}
}

// Get the current value
func (f *FibonacciSequence) Current() uint64 {
	return f.curr
}

// Advance the sequence, then return the current value (was the next value at the time of the call)
func (f *FibonacciSequence) Next() uint64 {
	f.prev, f.curr = f.curr, f.prev+f.curr
	return f.curr
}

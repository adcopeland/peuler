package main

import (
	"fmt"
)

func main() {
	solver := NewSolver()
	fmt.Println(solver.MaxSum(0, 0))
}

// Solver holds the memoized results
type Solver struct {
	memoizedResults [][]int
}

// Create a solver
func NewSolver() *Solver {
	solver := &Solver{
		memoizedResults: make([][]int, NUM_TRIANGLE_ROWS),
	}

	for rowNum, _ := range solver.memoizedResults {
		solver.memoizedResults[rowNum] = make([]int, rowNum+1)
	}

	return solver
}

// maxSum returns the max sum for a position given the max sum so far
func (solver *Solver) MaxSum(rowNum, rowPos int) int {
	// If this position already has a max sum, return it.
	result := solver.memoizedResults[rowNum][rowPos]
	if result != 0 {
		return result
	}

	// If there's no next row down, then the new max is just this value.
	// store and return the result.
	currentVal := getRow(rowNum)[rowPos]
	nextRowNum := rowNum + 1
	if nextRowNum >= NUM_TRIANGLE_ROWS {
		result = currentVal
		solver.memoizedResults[rowNum][rowPos] = result
		return result
	}

	// Otherwise, new max would be the larger of the MaxSum for the next row at the current
	// rowPos or the current rowPos + 1.
	// The next row always has 1 more item than this one, so no need to verify rowPos+1 exists.
	equalPosVal := solver.MaxSum(nextRowNum, rowPos)
	plusOnePosVal := solver.MaxSum(nextRowNum, rowPos+1)

	// Get the max
	max := equalPosVal
	if plusOnePosVal > max {
		max = plusOnePosVal
	}

	// store and return after adding in the current value
	result = max + currentVal
	solver.memoizedResults[rowNum][rowPos] = result
	return result
}

// Rest of the file is just accessing the problem data.
const NUM_TRIANGLE_ROWS = 15

var TRIANGLE = []int{
	75,
	95, 64,
	17, 47, 82,
	18, 35, 87, 10,
	20, 4, 82, 47, 65,
	19, 1, 23, 75, 3, 34,
	88, 2, 77, 73, 7, 63, 67,
	99, 65, 4, 28, 6, 16, 70, 92,
	41, 41, 26, 56, 83, 40, 80, 70, 33,
	41, 48, 72, 33, 47, 32, 37, 16, 94, 29,
	53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14,
	70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57,
	91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48,
	63, 66, 4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31,
	4, 62, 98, 27, 23, 9, 70, 98, 73, 93, 38, 53, 60, 4, 23,
}

func getRow(rowNum int) []int {
	rowNum++
	rowStart := 0
	for i := 1; i < rowNum; i++ {
		rowStart += i
	}
	rowEnd := rowStart + rowNum

	return TRIANGLE[rowStart:rowEnd]
}

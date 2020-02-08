package main

import (
  "fmt"
)

// Implement problem 21 (find the sum of all amicable numbers below 10000
func main() {
  numToSum := make(map[int]int)
  sumToNums := make(map[int][]int)

  // Build up all the sums
  for i := 1; i < 10000; i++ {
    sum := 0
    stop := i/2
    for j := 1; j <= stop; j++ {
      if i % j == 0 {
        sum += j
      }
    }
    numToSum[i] = sum
    sumToNums[sum] = append(sumToNums[sum], i)
  }

  // Figure out which numbers are amicable
  amicables := make(map[int]bool)
  for num, sum := range numToSum {
    if num != sum && numToSum[sum] == num {
      amicables[num] = true
      amicables[sum] = true
    }
  }

  // sum the amicable numbers
  sum := 0
  for amicable, _ := range amicables {
    sum += amicable
  }

  fmt.Println(sum)
}

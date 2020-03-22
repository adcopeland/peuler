package main

import (
  "fmt"
)

func main() {
  sum := 0
  abundantNumbers := make([]int, 0)
  for i := 1; i <= 28123; i++ {
    if isAbundant(i) {
      abundantNumbers = append(abundantNumbers, i)
    }
    if (!isSumOfTwoAbundants(i, abundantNumbers)) {
      sum += i
    }
  }

  fmt.Println(sum)
}


func isAbundant(n int) bool {
  sum := 1
  stop := n-1
  for i := 2; i < stop; i++ {
    if n % i == 0 {
      sum += i
      stop = n/i
      if stop != i {
        sum += stop
      }
    }
  }
  return sum > n
}

func isSumOfTwoAbundants(n int, abundantNumbers []int) bool {
  for i, abundantX := range abundantNumbers {
    smallestSum := abundantX + abundantX
    if smallestSum > n {
      break;
    }
    for j := i; j < len(abundantNumbers); j++ {
      sum := abundantX + abundantNumbers[j]
      if sum == n {
        return true
      }
      if sum > n {
        break
      }
    }
  }

  return false
}

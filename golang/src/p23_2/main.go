package main

import (
  "fmt"
  "runtime"
  "sync"
)

func main() {
  cpus := runtime.NumCPU()

  // First pass, the index will be 0 or 1 if abundant. Second pass, it'll be the list of abundant numbers.
  abundantNumbers := make([]int, 28123)

  // Use wait groups to sync tasks
  var abundantWG sync.WaitGroup
  abundantWG.Add(cpus)

  // Phase 1: stride through the data (earlier numbers are easier so striding helps balance it)
  // fill in 0 or 1 if the index is abundant or not
  for t := 0; t < cpus; t++ {
    go func(threadNum int) {
      for i := 1+threadNum; i <= 28123; i += cpus {
        if isAbundant(i) {
          abundantNumbers[i-1] = 1
        } else {
          abundantNumbers[i-1] = 0
        }
      }
      abundantWG.Done()
    }(t)
  }
  abundantWG.Wait()

  // Phase 2: In-place change abundantNumbers to the list of abundant numbers instead of 0/1 per index
  nextIndex := 0
  for i, num := range abundantNumbers {
    if num == 1 {
      abundantNumbers[nextIndex] = i+1
      nextIndex++
    }
  }
  abundantNumbers = abundantNumbers[0:nextIndex] // resize to the actual number of abundant numbers

  // Phase 3: split back out again and calculate per-thread sums
  var sumWG sync.WaitGroup
  sumWG.Add(cpus)

  sums := make([]int, cpus)
  for t := 0; t < cpus; t++ {
    go func(threadNum int) {
      for i := 1+threadNum; i <= 28123; i += cpus {
        if !isSumOfTwoAbundants(i, abundantNumbers) {
          sums[threadNum] += i
        }
      }
      sumWG.Done()
    }(t)
  }
  sumWG.Wait()

  // Phase 4: "merge" the per-thread sums
  sum := 0
  for _, s := range sums {
    sum += s
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

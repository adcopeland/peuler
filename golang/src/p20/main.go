package main

import (
  "fmt"
  "math/big"
)

func main() {
  facResult := big.NewInt(1)
  for i := 1; i <= 100; i++ {
    facResult = facResult.Mul(big.NewInt(int64(i)), facResult)
  }

  sum := 0
  for _, c := range facResult.String() {
    sum += int(c - '0')
  }

  fmt.Println(sum)
}

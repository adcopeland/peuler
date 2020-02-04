package main

import (
  "fmt"
  "time"
)

// How many Sundays fell on the first of the month from Jan 1, 1901 to Dec 31, 2000?
func main() {
  current := time.Date(1901, time.January, 1, 0, 0, 0, 0, time.UTC)
  end := time.Date(2000, time.December, 31, 0, 0, 0, 0, time.UTC)

  oneDay := 24*time.Hour
  result := 0
  for current.Before(end) {
    if current.Day() == 1 && current.Weekday() == time.Sunday {
      result++
    }
    current = current.Add(oneDay)
  }

  fmt.Println(result)
}

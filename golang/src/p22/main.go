package main

import (
  "fmt"
  "io/ioutil"
  "sort"
  "strings"
)

func main() {
  names := readNames()
  sort.Strings(names)

  totalScore := uint64(0)
  for i, name := range names {
    wordScore := uint64(0)
    for _, c := range name {
      wordScore += uint64(c - 'A') + uint64(1)
    }
    totalScore += wordScore * uint64(i+1)
  }

  fmt.Println(totalScore)
}

func readNames() []string {
  // The file is all names enclosed in quotes with commas on one line:
  // "NAME1","NAME2",...
  data, err := ioutil.ReadFile("../data/p022_names.txt")
  if err != nil {
    panic("Cannot open ../data/p022_names.txt: " + err.Error())
  }

  // First, split on comma
  names := strings.Split(string(data), ",")

  // Then, remove the quotes
  for i, n := range names {
    names[i] = strings.Trim(n, "\"")
  }

  return names
}

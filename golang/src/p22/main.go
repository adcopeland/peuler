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

  totalScore := 0
  for i, name := range names {
    wordScore := 0
    for _, c := range name {
      // Only works if names are all capital letters (they are). Add 1 since A is 1, not 0.
      wordScore += int(c - 'A') + 1
    }
    totalScore += wordScore * (i+1)
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

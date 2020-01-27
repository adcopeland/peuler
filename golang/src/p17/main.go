package main

import (
	"fmt"
	"strings"
)

// sum the count of letters in all numbers from 1 to 1000
func main() {
	sumLetters := 0
	for i := 1; i < 1000; i++ {
		sumLetters += lettersIn(i)
	}

	sumLetters += lettersInPhrase("one thousand")
	fmt.Println(sumLetters)
}

// used by lettersIn for numbers lower than 20
var uniques = []string{
	"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
	"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen",
}

// used by lettersIn to determine the tens prefix.
// "zero" and "teens" are placeholders so num/10 resolves to the right index.
var tens = []string{
	"zero", "teens", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety",
}

// Returns the number of letters in the english version of the number
func lettersIn(num int) int {
	if num >= 1000 {
		panic("lettersIn only works below 1000")
	}

	var sb strings.Builder
	if num >= 100 {
		numHundreds := num / 100
		sb.WriteString(uniques[numHundreds])
		sb.WriteString(" hundred ")
		num -= numHundreds * 100
		if num > 0 {
			sb.WriteString("and ")
		}
	}

	if num >= 20 {
		numTens := num / 10
		sb.WriteString(tens[numTens])
		sb.WriteRune(' ')
		num -= numTens * 10
	}

	if num > 0 {
		sb.WriteString(uniques[num])
	}

	return lettersInPhrase(sb.String())
}

// Returns any non-space letters in the provided string
func lettersInPhrase(phrase string) int {
	result := 0
	for _, r := range phrase {
		if r != ' ' {
			result++
		}
	}
	return result
}

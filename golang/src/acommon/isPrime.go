package acommon

import "math"

func IsPrime(n int) bool {
	stop := math.Sqrt(n)
	for i := 2; i <= stop; i++ {
		if n%i == 0 {
			return false
		}
	}
	return true
}

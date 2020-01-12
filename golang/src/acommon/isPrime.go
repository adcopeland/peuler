package acommon

func IsPrime(n int) bool {
	for i := 2; i <= n/i; i++ {
		if n%i == 0 {
			return false
		}
	}
	return true
}

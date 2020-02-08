package acommon

// Retrieve the list of factors for n
func GetFactors(n uint64) []uint64 {
	result := make([]uint64, 0)

	for i := uint64(2); i < n; i++ {
		if n%i == 0 {
			result = append(result, i)
			n /= i
			i = 1
		}
	}

	if n != 1 {
		result = append(result, n)
	}

	return result
}

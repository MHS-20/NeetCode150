package bitmanipulation

func hammingWeight(n int) int {
	count := 0

	for n != 0 {
		n = n & (n - 1) // clears the lowest set bit
		count++
	}
	return count
}

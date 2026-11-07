package main

func maxChunksToSorted(arr []int) int {
	n := len(arr)
	prefixMax, suffixMin := make([]int, n), make([]int, n)

	prefixMax[0] = arr[0]
	for i := 1; i < n; i++ {
		prefixMax[i] = max(prefixMax[i-1], arr[i])
	}

	suffixMin[n-1] = arr[n-1]
	for i := n - 2; i >= 0; i-- {
		suffixMin[i] = min(suffixMin[i+1], arr[i])
	}

	chunks := 1 // the last chunk always exists
	for i := 0; i < n-1; i++ {
		if prefixMax[i] <= suffixMin[i+1] {
			chunks++
		}
	}

	return chunks
}

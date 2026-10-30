package main

import "math"

func maxChunksToSorted(arr []int) int {
	n := len(arr)
	sufMin := make([]int, n+1)
	sufMin[n] = math.MaxInt
	for i := n - 1; i >= 0; i-- {
		sufMin[i] = min(sufMin[i+1], arr[i])
	}

	chunks, prefMax := 0, math.MinInt
	for i := 0; i < n; i++ {
		prefMax = max(prefMax, arr[i])
		if prefMax <= sufMin[i+1] {
			chunks++ // valid cut after i (i = n-1 always counts)
		}
	}
	return chunks
}

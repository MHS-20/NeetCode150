package main

import "sort"

func topKFrequent(nums []int, k int) []int {
	freq := make(map[int]int)
	for _, n := range nums {
		freq[n]++
	}

	keys := make([]int, 0, len(freq))
	for key := range freq {
		keys = append(keys, key)
	}

	sort.Slice(keys, func(i, j int) bool { return freq[keys[i]] > freq[keys[j]] })

	return keys[:k]
}

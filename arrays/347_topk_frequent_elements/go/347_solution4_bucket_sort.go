package main

func topKFrequent(nums []int, k int) []int {
	freq := make(map[int]int)
	for _, n := range nums {
		freq[n]++
	}

	buckets := make([][]int, len(nums)+1)
	for val, cnt := range freq {
		buckets[cnt] = append(buckets[cnt], val)
	}

	res := make([]int, 0, k)
	for i := len(buckets) - 1; i >= 0 && len(res) < k; i-- {
		for _, val := range buckets[i] {
			res = append(res, val)
			if len(res) == k {
				break
			}
		}
	}

	return res
}

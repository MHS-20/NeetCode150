package solution

import "sort"

func containsDuplicate(nums []int) bool {
	sorted := make([]int, len(nums))
	copy(sorted, nums)
	sort.Ints(sorted)

	for i := 1; i < len(sorted); i++ {
		if sorted[i] == sorted[i-1] {
			return true
		}
	}

	return false
}

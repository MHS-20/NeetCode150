package backtracking

import "sort"

func subsetsWithDup(nums []int) [][]int {
	var result [][]int
	var cur []int
	sort.Ints(nums)

	var backtrack func(idx int)
	backtrack = func(idx int) {
		if idx == len(nums) {
			result = append(result, append([]int(nil), cur...))
			return
		}

		cur = append(cur, nums[idx])
		backtrack(idx + 1)
		cur = cur[:len(cur)-1]

		i := idx + 1
		for i < len(nums) && nums[idx] == nums[i] {
			i++
		}

		backtrack(i)
	}

	backtrack(0)
	return result
}

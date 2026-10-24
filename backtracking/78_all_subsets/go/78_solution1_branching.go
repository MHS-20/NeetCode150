package backtracking

func subsets(nums []int) [][]int {
	var result [][]int
	var cur []int

	var backtrack func(idx int)
	backtrack = func(idx int) {
		if idx == len(nums) {
			result = append(result, append([]int(nil), cur...))
			return
		}
		// include nums[idx]
		cur = append(cur, nums[idx])
		backtrack(idx + 1)
		cur = cur[:len(cur)-1] // undo

		// skip nums[idx]
		backtrack(idx + 1)
	}

	backtrack(0)
	return result
}

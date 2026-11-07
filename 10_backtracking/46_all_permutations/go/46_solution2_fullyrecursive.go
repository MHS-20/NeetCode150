package backtracking

func permute(nums []int) [][]int {
	var result [][]int

	var backtrack func(idx, i int)
	backtrack = func(idx, i int) {
		if idx == len(nums) {
			result = append(result, append([]int(nil), nums...))
			return
		}
		if i == len(nums) {
			return
		}

		// choose nums[i] for position idx, then fix the next position
		nums[idx], nums[i] = nums[i], nums[idx]
		backtrack(idx+1, idx+1)
		nums[idx], nums[i] = nums[i], nums[idx] // undo

		// try the next candidate for the same position
		backtrack(idx, i+1)
	}

	backtrack(0, 0)
	return result
}

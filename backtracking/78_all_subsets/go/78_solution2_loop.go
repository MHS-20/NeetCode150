package backtracking

func subsets(nums []int) [][]int {
	var result [][]int
	var cur []int

	var backtrack func(start int)
	backtrack = func(start int) {
		result = append(result, append([]int(nil), cur...)) // every path is a valid subset

		for i := start; i < len(nums); i++ {
			cur = append(cur, nums[i])
			backtrack(i + 1)
			cur = cur[:len(cur)-1] // undo
		}
	}

	backtrack(0)
	return result
}

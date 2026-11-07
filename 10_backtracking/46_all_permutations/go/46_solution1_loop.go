package backtracking

func permute(nums []int) [][]int {
	var result [][]int
	cur := append([]int(nil), nums...)

	var backtrack func(idx int)
	backtrack = func(idx int) {
		if idx == len(cur) {
			result = append(result, append([]int(nil), cur...))
			return
		}

		for i := idx; i < len(cur); i++ {
			cur[idx], cur[i] = cur[i], cur[idx]
			backtrack(idx + 1)
			cur[idx], cur[i] = cur[i], cur[idx]
		}
	}

	backtrack(0)
	return result
}

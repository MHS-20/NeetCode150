package backtracking

func combinationSum(candidates []int, target int) [][]int {
	var result [][]int
	var cur []int

	var backtrack func(idx, sum int)
	backtrack = func(idx, sum int) {
		if sum == target {
			result = append(result, append([]int(nil), cur...))
			return
		}
		if sum > target || idx >= len(candidates) {
			return
		}

		// include candidates[idx], stay on idx (can reuse it)
		cur = append(cur, candidates[idx])
		backtrack(idx, sum+candidates[idx])
		cur = cur[:len(cur)-1]

		// skip candidates[idx] for good, move on
		backtrack(idx+1, sum)
	}

	backtrack(0, 0)
	return result
}

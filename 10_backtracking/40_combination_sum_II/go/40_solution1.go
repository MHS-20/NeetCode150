package backtracking

import "sort"

func combinationSum2(candidates []int, target int) [][]int {
	var result [][]int
	var cur []int
	sort.Ints(candidates)

	var backtrack func(idx, sum int)
	backtrack = func(idx, sum int) {
		if sum == target {
			result = append(result, append([]int(nil), cur...))
			return
		}

		if sum > target || idx == len(candidates) {
			return
		}

		cur = append(cur, candidates[idx])
		backtrack(idx+1, sum+candidates[idx])
		cur = cur[:len(cur)-1]

		i := idx + 1
		for i < len(candidates) && candidates[i] == candidates[idx] {
			i++
		}
		backtrack(i, sum)
	}

	backtrack(0, 0)
	return result
}

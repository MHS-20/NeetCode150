package intervals

import "slices"

func merge(intervals [][]int) [][]int {
	slices.SortFunc(intervals, func(a, b []int) int {
		if a[0] != b[0] {
			return a[0] - b[0]
		}
		return a[1] - b[1]
	})
	result := [][]int{}

	for _, cur := range intervals {
		if len(result) == 0 || result[len(result)-1][1] < cur[0] {
			result = append(result, cur)
		} else {
			last := result[len(result)-1]
			last[1] = max(last[1], cur[1])
		}
	}

	return result
}

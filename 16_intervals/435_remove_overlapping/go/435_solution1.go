package intervals

import "slices"

func eraseOverlapIntervals(intervals [][]int) int {
	slices.SortFunc(intervals, func(a, b []int) int {
		if a[0] != b[0] {
			return a[0] - b[0]
		}
		return a[1] - b[1]
	})
	kept := 0
	lastEnd := 0 // end of the last kept interval

	for _, cur := range intervals {
		if kept == 0 || lastEnd <= cur[0] {
			kept++
			lastEnd = cur[1]
		} else if lastEnd > cur[1] {
			lastEnd = cur[1] // overlap: keep the one that ends earlier
		}
	}

	return len(intervals) - kept
}

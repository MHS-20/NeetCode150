package main

func largestRectangleArea(heights []int) int {
	st := []int{} // indices of increasing heights
	best := 0

	for i := 0; i <= len(heights); i++ {
		h := 0 // sentinel flushes the stack
		if i < len(heights) {
			h = heights[i]
		}
		for len(st) > 0 && heights[st[len(st)-1]] > h {
			height := heights[st[len(st)-1]]
			st = st[:len(st)-1]
			prev := -1
			if len(st) > 0 {
				prev = st[len(st)-1]
			}
			best = max(best, height*(i-prev-1))
		}
		st = append(st, i)
	}
	return best
}

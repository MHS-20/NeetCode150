package main

func maxChunksToSorted(arr []int) int {
	st := []int{} // max of each chunk, non-decreasing
	for _, x := range arr {
		curMax := x
		for len(st) > 0 && st[len(st)-1] > x {
			curMax = max(curMax, st[len(st)-1])
			st = st[:len(st)-1]
		}
		st = append(st, curMax)
	}
	return len(st)
}

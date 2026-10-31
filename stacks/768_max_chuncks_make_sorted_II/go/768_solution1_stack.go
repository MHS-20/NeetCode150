package main

func maxChunksToSorted(arr []int) int {
	st := []int{}

	for _, n := range arr {
		if len(st) == 0 || n > st[len(st)-1] {
			st = append(st, n)
		} else {
			mx := st[len(st)-1]
			st = st[:len(st)-1]
			for len(st) > 0 && n <= st[len(st)-1] {
				st = st[:len(st)-1]
			}
			st = append(st, mx)
		}
	}

	return len(st)
}

// ---- Alternative Compact Version ----
// func maxChunksToSorted(arr []int) int {
// 	st := []int{} // max of each chunk, non-decreasing
// 	for _, x := range arr {
// 		curMax := x
// 		for len(st) > 0 && st[len(st)-1] > x {
// 			curMax = max(curMax, st[len(st)-1])
// 			st = st[:len(st)-1]
// 		}
// 		st = append(st, curMax)
// 	}
// 	return len(st)
// }

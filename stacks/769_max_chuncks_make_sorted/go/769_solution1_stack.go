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

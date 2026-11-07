package main

func dailyTemperatures(temps []int) []int {
	res := make([]int, len(temps))
	st := []int{} // indices with no warmer day yet

	for i, t := range temps {
		for len(st) > 0 && t > temps[st[len(st)-1]] {
			j := st[len(st)-1]
			st = st[:len(st)-1]
			res[j] = i - j
		}
		st = append(st, i)
	}
	return res
}

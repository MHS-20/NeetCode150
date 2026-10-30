package greedy

func canCompleteCircuit(gas []int, cost []int) int {
	total, cur, start := 0, 0, 0
	for i := range gas {
		diff := gas[i] - cost[i]
		total += diff
		cur += diff
		if cur < 0 {
			start = i + 1
			cur = 0
		}
	}
	if total < 0 {
		return -1
	}
	return start
}

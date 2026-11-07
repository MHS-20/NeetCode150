package greedy

import "sort"

func isNStraightHand(hand []int, groupSize int) bool {
	if len(hand)%groupSize != 0 {
		return false
	}

	count := make(map[int]int)
	for _, c := range hand {
		count[c]++
	}

	// ascending, so each value is the smallest remaining card when reached
	keys := make([]int, 0, len(count))
	for k := range count {
		keys = append(keys, k)
	}
	sort.Ints(keys)

	for _, start := range keys {
		c := count[start]
		if c == 0 {
			continue // already used up by earlier groups
		}
		for v := start; v < start+groupSize; v++ {
			if count[v] < c {
				return false // missing value, group can't be built
			}
			count[v] -= c
		}
	}

	return true
}

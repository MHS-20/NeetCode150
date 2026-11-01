package greedy

func mergeTriplets(triplets [][]int, target []int) bool {
	var found [3]bool

	for _, t := range triplets {
		if t[0] > target[0] || t[1] > target[1] || t[2] > target[2] {
			continue
		}
		for i := 0; i < 3; i++ {
			if t[i] == target[i] {
				found[i] = true
			}
		}
	}

	return found[0] && found[1] && found[2]
}

package main

func checkInclusion(s1 string, s2 string) bool {
	k := len(s1)
	diff := map[byte]int{}
	mismatched := 0

	// shift a letter's diff by delta, keeping `mismatched` in sync
	update := func(c byte, delta int) {
		if diff[c] == 0 {
			mismatched++ // was balanced, about to break
		}
		diff[c] += delta
		if diff[c] == 0 {
			mismatched-- // now balanced again
		}
	}

	for i := 0; i < k; i++ {
		update(s1[i], -1)
	}

	for right := 0; right < len(s2); right++ {
		update(s2[right], +1) // char enters
		if right >= k {
			update(s2[right-k], -1) // char leaves
		}
		if mismatched == 0 {
			return true
		}
	}
	return false
}

package main

func minEatingSpeed(piles []int, h int) int {
	maxPile := 0
	for _, p := range piles {
		if p > maxPile {
			maxPile = p
		}
	}

	left, right := 1, maxPile
	for left < right {
		k := left + (right-left)/2
		hours := 0
		for _, p := range piles {
			hours += (p + k - 1) / k
		}

		if hours > h {
			left = k + 1
		} else {
			right = k
		}
	}
	return left
}

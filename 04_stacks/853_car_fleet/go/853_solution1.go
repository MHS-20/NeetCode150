package main

import "sort"

func carFleet(target int, position []int, speed []int) int {
	idx := make([]int, len(position))
	for i := range idx {
		idx[i] = i
	}
	sort.Slice(idx, func(a, b int) bool { return position[idx[a]] > position[idx[b]] })

	fleets := 0
	slowest := 0.0 // arrival time of the fleet ahead
	for _, i := range idx {
		hours := float64(target-position[i]) / float64(speed[i])
		if hours > slowest {
			fleets++
			slowest = hours
		}
	}
	return fleets
}

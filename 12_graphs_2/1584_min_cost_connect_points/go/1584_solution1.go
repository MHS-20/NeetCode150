package graphs

import "math"

func minCostConnectPoints(points [][]int) int {
	n := len(points)
	minCost := make([]int, n)
	inTree := make([]bool, n)
	for i := range minCost {
		minCost[i] = math.MaxInt
	}
	minCost[0] = 0
	cost := 0

	abs := func(x int) int {
		if x < 0 {
			return -x
		}
		return x
	}

	for step := 0; step < n; step++ {
		// 1. Pick the cheapest point not yet in the tree
		u := -1
		for i := 0; i < n; i++ {
			if !inTree[i] && (u == -1 || minCost[i] < minCost[u]) {
				u = i
			}
		}

		// 2. Add it
		inTree[u] = true
		cost += minCost[u]

		// 3. Update the outside points' best connection
		for i := 0; i < n; i++ {
			if inTree[i] {
				continue
			}
			dist := abs(points[i][0]-points[u][0]) + abs(points[i][1]-points[u][1])
			minCost[i] = min(minCost[i], dist)
		}
	}
	return cost
}

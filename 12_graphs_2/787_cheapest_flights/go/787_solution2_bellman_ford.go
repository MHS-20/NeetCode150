package graphs

import "math"

func findCheapestPrice(n int, flights [][]int, src int, dst int, k int) int {
	prices := make([]int, n)
	for i := range prices {
		prices[i] = math.MaxInt
	}
	prices[src] = 0

	// Bellman-Ford limited to k + 1 rounds: round i allows i flights
	for round := 0; round <= k; round++ {
		next := append([]int(nil), prices...) // reads come from the previous round only
		for _, f := range flights {
			from, to, price := f[0], f[1], f[2]
			if prices[from] != math.MaxInt && prices[from]+price < next[to] {
				next[to] = prices[from] + price
			}
		}
		prices = next
	}

	if prices[dst] == math.MaxInt {
		return -1
	}
	return prices[dst]
}

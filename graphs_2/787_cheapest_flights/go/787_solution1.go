package graphs

import "math"

func findCheapestPrice(n int, flights [][]int, src int, dst int, k int) int {
	type edge struct{ to, price int }
	type state struct{ city, cost int }

	adj := make([][]edge, n) // from -> {to, price}
	for _, f := range flights {
		adj[f[0]] = append(adj[f[0]], edge{f[1], f[2]})
	}

	prices := make([]int, n)
	for i := range prices {
		prices[i] = math.MaxInt
	}
	q := []state{{src, 0}}
	prices[src] = 0

	for flightsUsed := 0; flightsUsed <= k && len(q) > 0; flightsUsed++ {
		sz := len(q)
		for i := 0; i < sz; i++ {
			cur := q[0]
			q = q[1:]
			for _, e := range adj[cur.city] {
				if cur.cost+e.price < prices[e.to] {
					prices[e.to] = cur.cost + e.price
					q = append(q, state{e.to, cur.cost + e.price})
				}
			}
		}
	}

	if prices[dst] == math.MaxInt {
		return -1
	}
	return prices[dst]
}

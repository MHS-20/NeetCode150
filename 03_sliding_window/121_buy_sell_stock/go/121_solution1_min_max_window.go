package main

import "math"

func maxProfit(prices []int) int {
	mn := math.MaxInt
	profit := 0

	for _, p := range prices {
		if p < mn {
			mn = p
		}

		if p-mn > profit {
			profit = p - mn
		}
	}

	return profit
}

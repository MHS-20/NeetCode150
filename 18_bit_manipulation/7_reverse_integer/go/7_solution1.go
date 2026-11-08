package bitmanipulation

import "math"

func reverse(x int) int {
	res := 0

	for x != 0 {
		d := x % 10
		x = x / 10

		if res > math.MaxInt32/10 || res < math.MinInt32/10 {
			return 0
		}
		res = res*10 + d
	}

	return res
}

package mathgeometry

func myPow(x float64, n int) float64 {
	N := n
	neg := N < 0
	if neg {
		N = -N
	}

	res := 1.0
	for N > 0 {
		if N&1 == 1 {
			res *= x
		}
		x *= x
		N >>= 1
	}
	if neg {
		return 1 / res
	}
	return res
}

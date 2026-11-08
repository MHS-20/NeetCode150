package mathgeometry

type DetectSquares struct {
	cnt map[[2]int]int
}

func Constructor() DetectSquares {
	return DetectSquares{cnt: map[[2]int]int{}}
}

func (this *DetectSquares) Add(point []int) {
	this.cnt[[2]int{point[0], point[1]}]++
}

func abs(a int) int {
	if a < 0 {
		return -a
	}
	return a
}

func (this *DetectSquares) Count(point []int) int {
	x, y, res := point[0], point[1], 0

	for p, c := range this.cnt {
		px, py := p[0], p[1]
		if px == x || abs(px-x) != abs(py-y) {
			continue // must be a diagonal corner with side length > 0
		}
		res += c * this.cnt[[2]int{x, py}] * this.cnt[[2]int{px, y}]
	}
	return res
}

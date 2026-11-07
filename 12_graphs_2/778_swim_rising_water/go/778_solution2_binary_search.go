package graphs

func swimInWater(grid [][]int) int {
	n := len(grid)
	dirs := [4][2]int{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}

	canReach := func(t int) bool {
		if grid[0][0] > t {
			return false
		}
		visited := make([][]bool, n)
		for i := range visited {
			visited[i] = make([]bool, n)
		}
		q := [][2]int{{0, 0}}
		visited[0][0] = true

		for len(q) > 0 {
			r, c := q[0][0], q[0][1]
			q = q[1:]
			if r == n-1 && c == n-1 {
				return true
			}
			for _, d := range dirs {
				nr, nc := r+d[0], c+d[1]
				if nr < 0 || nc < 0 || nr >= n || nc >= n {
					continue
				}
				if visited[nr][nc] || grid[nr][nc] > t {
					continue
				}
				visited[nr][nc] = true
				q = append(q, [2]int{nr, nc})
			}
		}
		return false
	}

	lo, hi := 0, n*n-1
	for lo < hi {
		mid := lo + (hi-lo)/2
		if canReach(mid) {
			hi = mid // works: try lower
		} else {
			lo = mid + 1 // fails: need more water
		}
	}
	return lo
}

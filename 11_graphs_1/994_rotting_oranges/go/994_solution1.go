package graphs

func orangesRotting(grid [][]int) int {
	dirs := [4][2]int{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}
	rows, cols := len(grid), len(grid[0])
	var q [][2]int
	fresh := 0

	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			if grid[i][j] == 2 {
				q = append(q, [2]int{i, j})
			} else if grid[i][j] == 1 {
				fresh++
			}
		}
	}

	minutes := 0
	for len(q) > 0 && fresh > 0 {
		sz := len(q)
		minutes++
		for k := 0; k < sz; k++ {
			r, c := q[0][0], q[0][1]
			q = q[1:]
			for _, d := range dirs {
				nr, nc := r+d[0], c+d[1]
				if nr < 0 || nc < 0 || nr >= rows || nc >= cols {
					continue
				}
				if grid[nr][nc] != 1 {
					continue
				}

				grid[nr][nc] = 2
				fresh--
				q = append(q, [2]int{nr, nc})
			}
		}
	}
	if fresh == 0 {
		return minutes
	}
	return -1
}

package graphs

import "math"

var dirs = [4][2]int{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}

func islandsAndTreasure(grid [][]int) {
	rows, cols := len(grid), len(grid[0])
	var q [][2]int

	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			if grid[i][j] == 0 {
				q = append(q, [2]int{i, j})
			}
		}
	}

	for len(q) > 0 {
		r, c := q[0][0], q[0][1]
		q = q[1:]
		for _, d := range dirs {
			nr, nc := r+d[0], c+d[1]
			if nr < 0 || nc < 0 || nr >= rows || nc >= cols {
				continue
			}
			if grid[nr][nc] != math.MaxInt32 {
				continue
			}

			grid[nr][nc] = grid[r][c] + 1
			q = append(q, [2]int{nr, nc})
		}
	}
}

package graphs

var dirs = [4][2]int{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}

func numIslands(grid [][]byte) int {
	if len(grid) == 0 {
		return 0
	}
	rows, cols := len(grid), len(grid[0])
	count := 0
	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			if grid[i][j] == '1' {
				sink(grid, i, j, rows, cols)
				count++
			}
		}
	}
	return count
}

func sink(grid [][]byte, r, c, rows, cols int) {
	q := [][2]int{{r, c}}
	grid[r][c] = '0'
	for len(q) > 0 {
		cur := q[0]
		q = q[1:]
		for _, d := range dirs {
			nr, nc := cur[0]+d[0], cur[1]+d[1]
			if nr >= 0 && nc >= 0 && nr < rows && nc < cols && grid[nr][nc] == '1' {
				grid[nr][nc] = '0'
				q = append(q, [2]int{nr, nc})
			}
		}
	}
}

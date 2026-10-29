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
	if r < 0 || c < 0 || r >= rows || c >= cols || grid[r][c] != '1' {
		return
	}
	grid[r][c] = '0'
	for _, d := range dirs {
		sink(grid, r+d[0], c+d[1], rows, cols)
	}
}

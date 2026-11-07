package graphs

var dirs = [4][2]int{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}

func solve(board [][]byte) {
	rows, cols := len(board), len(board[0])

	var dfs func(r, c int)
	dfs = func(r, c int) {
		if r < 0 || c < 0 || r >= rows || c >= cols || board[r][c] != 'O' {
			return
		}
		board[r][c] = '.'
		for _, d := range dirs {
			dfs(r+d[0], c+d[1])
		}
	}

	// 1. mark border-connected 'O's as safe
	for i := 0; i < rows; i++ {
		dfs(i, 0)
		dfs(i, cols-1)
	}
	for j := 0; j < cols; j++ {
		dfs(0, j)
		dfs(rows-1, j)
	}

	// 2. capture leftover 'O's, restore safe ones
	for _, row := range board {
		for j, cell := range row {
			if cell == 'O' {
				row[j] = 'X'
			} else if cell == '.' {
				row[j] = 'O'
			}
		}
	}
}

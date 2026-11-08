package backtracking

var dirs = [4][2]int{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}

func exist(board [][]byte, word string) bool {
	var dfs func(idx, row, col int) bool
	dfs = func(idx, row, col int) bool {
		ch := word[idx]
		if ch != board[row][col] {
			return false
		}

		if idx == len(word)-1 {
			return true
		}

		board[row][col] = '#'
		for _, d := range dirs {
			nr, nc := row+d[0], col+d[1]

			if nr < 0 || nr >= len(board) || nc < 0 || nc >= len(board[0]) {
				continue
			}

			if dfs(idx+1, nr, nc) {
				board[row][col] = ch // restore before returning, so the board is unchanged
				return true
			}
		}

		board[row][col] = ch
		return false
	}

	for r := range board {
		for c := range board[0] {
			if dfs(0, r, c) {
				return true
			}
		}
	}
	return false
}

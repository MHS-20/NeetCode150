package backtracking

import "strings"

func solveNQueens(n int) [][]string {
	var result [][]string
	board := make([][]byte, n)
	for r := range board {
		board[r] = []byte(strings.Repeat(".", n))
	}
	cols := make([]bool, n)
	diag1 := make([]bool, 2*n-1)
	diag2 := make([]bool, 2*n-1)

	var backtrack func(row int)
	backtrack = func(row int) {
		if row == n {
			snapshot := make([]string, n)
			for r := range board {
				snapshot[r] = string(board[r])
			}
			result = append(result, snapshot)
			return
		}

		for col := 0; col < n; col++ {
			d1 := row + col         // "/" diagonal
			d2 := row - col + n - 1 // "\" diagonal, shifted
			if cols[col] || diag1[d1] || diag2[d2] {
				continue
			}

			board[row][col] = 'Q'
			cols[col], diag1[d1], diag2[d2] = true, true, true

			backtrack(row + 1)

			board[row][col] = '.'
			cols[col], diag1[d1], diag2[d2] = false, false, false
		}
	}

	backtrack(0)
	return result
}

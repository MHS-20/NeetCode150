package main

func isValidSudoku(board [][]byte) bool {
	var seen [9]bool

	for i := 0; i < 9; i++ {
		for j := 0; j < 9; j++ {
			if board[i][j] == '.' {
				continue
			}
			current := board[i][j] - '0' - 1
			if seen[current] {
				return false
			}
			seen[current] = true
		}
		seen = [9]bool{}
	}

	for j := 0; j < 9; j++ {
		for i := 0; i < 9; i++ {
			if board[i][j] == '.' {
				continue
			}
			current := board[i][j] - '0' - 1
			if seen[current] {
				return false
			}
			seen[current] = true
		}
		seen = [9]bool{}
	}

	for rowOffset := 0; rowOffset < 9; rowOffset += 3 {
		for colOffset := 0; colOffset < 9; colOffset += 3 {
			for i := 0; i < 3; i++ {
				for j := 0; j < 3; j++ {
					val := board[i+rowOffset][j+colOffset]
					if val == '.' {
						continue
					}
					current := val - '0' - 1
					if seen[current] {
						return false
					}
					seen[current] = true
				}
			}
			seen = [9]bool{}
		}
	}

	return true
}

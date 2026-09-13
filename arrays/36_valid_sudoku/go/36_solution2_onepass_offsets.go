package main

func isValidSudoku(board [][]byte) bool {
	var seenGrid [9]bool
	var seenCol [9][9]bool
	var seenRow [9][9]bool

	for rowOffset := 0; rowOffset < 9; rowOffset += 3 {
		for colOffset := 0; colOffset < 9; colOffset += 3 {
			for i := 0; i < 3; i++ {
				for j := 0; j < 3; j++ {
					val := board[i+rowOffset][j+colOffset]
					if val == '.' {
						continue
					}

					current := val - '0' - 1

					if seenGrid[current] {
						return false
					}
					seenGrid[current] = true

					if seenRow[i+rowOffset][current] {
						return false
					}
					seenRow[i+rowOffset][current] = true

					if seenCol[j+colOffset][current] {
						return false
					}
					seenCol[j+colOffset][current] = true
				}
			}
			seenGrid = [9]bool{}
		}
	}

	return true
}

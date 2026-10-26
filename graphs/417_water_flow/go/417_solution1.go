package graphs

import "math"

var dirs = [4][2]int{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}

func pacificAtlantic(heights [][]int) [][]int {
	rows, cols := len(heights), len(heights[0])
	pacific, atlantic := newGrid(rows, cols), newGrid(rows, cols)

	var dfs func(ocean [][]bool, r, c, prevHeight int)
	dfs = func(ocean [][]bool, r, c, prevHeight int) {
		if r < 0 || c < 0 || r >= rows || c >= cols {
			return
		}
		if ocean[r][c] || heights[r][c] < prevHeight {
			return
		}

		ocean[r][c] = true
		for _, d := range dirs {
			dfs(ocean, r+d[0], c+d[1], heights[r][c])
		}
	}

	for i := 0; i < rows; i++ {
		dfs(pacific, i, 0, math.MinInt)
		dfs(atlantic, i, cols-1, math.MinInt)
	}
	for j := 0; j < cols; j++ {
		dfs(pacific, 0, j, math.MinInt)
		dfs(atlantic, rows-1, j, math.MinInt)
	}

	var result [][]int
	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			if pacific[i][j] && atlantic[i][j] {
				result = append(result, []int{i, j})
			}
		}
	}
	return result
}

func newGrid(rows, cols int) [][]bool {
	g := make([][]bool, rows)
	for i := range g {
		g[i] = make([]bool, cols)
	}
	return g
}

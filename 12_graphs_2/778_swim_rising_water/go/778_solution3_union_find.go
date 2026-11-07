package graphs

func swimInWater(grid [][]int) int {
	n := len(grid)
	parent := make([]int, n*n)
	rnk := make([]int, n*n)
	for i := range parent {
		parent[i] = i
	}

	find := func(x int) int {
		for parent[x] != x {
			parent[x] = parent[parent[x]] // path halving
			x = parent[x]
		}
		return x
	}

	unite := func(a, b int) {
		a, b = find(a), find(b)
		if a == b {
			return
		}
		if rnk[a] < rnk[b] {
			a, b = b, a
		}
		parent[b] = a
		if rnk[a] == rnk[b] {
			rnk[a]++
		}
	}

	// pos[v] = cell index holding elevation v
	pos := make([]int, n*n)
	for r := 0; r < n; r++ {
		for c := 0; c < n; c++ {
			pos[grid[r][c]] = r*n + c
		}
	}

	dirs := [4][2]int{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}

	for t := 0; t < n*n; t++ {
		r, c := pos[t]/n, pos[t]%n // this cell becomes submerged
		for _, d := range dirs {
			nr, nc := r+d[0], c+d[1]
			if nr < 0 || nc < 0 || nr >= n || nc >= n {
				continue
			}
			if grid[nr][nc] <= t { // neighbor already submerged
				unite(r*n+c, nr*n+nc)
			}
		}
		if find(0) == find(n*n-1) {
			return t
		}
	}
	return -1
}

package graphs

import "container/heap"

type cell struct{ elev, r, c int }

type cellHeap []cell

func (h cellHeap) Len() int           { return len(h) }
func (h cellHeap) Less(i, j int) bool { return h[i].elev < h[j].elev }
func (h cellHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *cellHeap) Push(x any)        { *h = append(*h, x.(cell)) }
func (h *cellHeap) Pop() any {
	old := *h
	x := old[len(old)-1]
	*h = old[:len(old)-1]
	return x
}

func swimInWater(grid [][]int) int {
	n := len(grid)
	visited := make([][]bool, n)
	for i := range visited {
		visited[i] = make([]bool, n)
	}
	pq := &cellHeap{}
	dirs := [4][2]int{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}

	heap.Push(pq, cell{grid[0][0], 0, 0})
	visited[0][0] = true
	t := 0

	for pq.Len() > 0 {
		e := heap.Pop(pq).(cell)
		t = max(t, e.elev)
		if e.r == n-1 && e.c == n-1 {
			return t
		}

		for _, d := range dirs {
			nr, nc := e.r+d[0], e.c+d[1]
			if nr < 0 || nc < 0 || nr >= n || nc >= n || visited[nr][nc] {
				continue
			}
			visited[nr][nc] = true
			heap.Push(pq, cell{grid[nr][nc], nr, nc})
		}
	}
	return -1
}

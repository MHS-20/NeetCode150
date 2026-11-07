package graphs

import "container/heap"

type edge struct{ to, w int }

type item struct{ d, node int }

type minHeap []item

func (h minHeap) Len() int           { return len(h) }
func (h minHeap) Less(i, j int) bool { return h[i].d < h[j].d }
func (h minHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *minHeap) Push(x any)        { *h = append(*h, x.(item)) }
func (h *minHeap) Pop() any {
	old := *h
	x := old[len(old)-1]
	*h = old[:len(old)-1]
	return x
}

func networkDelayTime(times [][]int, n int, k int) int {
	adj := make([][]edge, n+1) // node -> {neighbor, weight}
	for _, t := range times {
		adj[t[0]] = append(adj[t[0]], edge{t[1], t[2]})
	}

	const inf = int(^uint(0) >> 1)
	dist := make([]int, n+1)
	for i := range dist {
		dist[i] = inf
	}
	dist[k] = 0
	pq := &minHeap{{0, k}}

	for pq.Len() > 0 {
		cur := heap.Pop(pq).(item)
		if cur.d > dist[cur.node] {
			continue // stale entry
		}
		for _, e := range adj[cur.node] {
			if cur.d+e.w < dist[e.to] {
				dist[e.to] = cur.d + e.w
				heap.Push(pq, item{dist[e.to], e.to})
			}
		}
	}

	ans := 0
	for _, d := range dist[1:] {
		ans = max(ans, d)
	}
	if ans == inf {
		return -1
	}
	return ans
}

package intervals

import (
	"container/heap"
	"sort"
)

type entry struct{ size, end int }

type minHeap []entry

func (h minHeap) Len() int { return len(h) }
func (h minHeap) Less(i, j int) bool {
	return h[i].size < h[j].size || (h[i].size == h[j].size && h[i].end < h[j].end)
}
func (h minHeap) Swap(i, j int)  { h[i], h[j] = h[j], h[i] }
func (h *minHeap) Push(x any)   { *h = append(*h, x.(entry)) }
func (h *minHeap) Pop() any {
	old := *h
	x := old[len(old)-1]
	*h = old[:len(old)-1]
	return x
}

func minInterval(intervals [][]int, queries []int) []int {
	result := make([]int, len(queries))
	idx := make([]int, len(queries))
	for k := range idx {
		idx[k] = k
	}

	sort.Slice(intervals, func(a, b int) bool { return intervals[a][0] < intervals[b][0] })
	sort.Slice(idx, func(a, b int) bool { return queries[idx[a]] < queries[idx[b]] })

	h := &minHeap{}
	i, n := 0, len(intervals)
	for _, j := range idx {
		q := queries[j]

		for i < n && intervals[i][0] <= q {
			heap.Push(h, entry{intervals[i][1] - intervals[i][0] + 1, intervals[i][1]})
			i++
		}

		for h.Len() > 0 && (*h)[0].end < q {
			heap.Pop(h)
		}

		if h.Len() == 0 {
			result[j] = -1
		} else {
			result[j] = (*h)[0].size
		}
	}

	return result
}

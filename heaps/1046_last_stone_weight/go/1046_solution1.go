package heaps

import (
	"container/heap"
	"sort"
)

type maxHeap struct{ sort.IntSlice }

func (h maxHeap) Less(i, j int) bool { return h.IntSlice[i] > h.IntSlice[j] }

func (h *maxHeap) Push(x any) { h.IntSlice = append(h.IntSlice, x.(int)) }

func (h *maxHeap) Pop() any {
	old := h.IntSlice
	x := old[len(old)-1]
	h.IntSlice = old[:len(old)-1]
	return x
}

func lastStoneWeight(stones []int) int {
	pq := &maxHeap{stones}
	heap.Init(pq)

	for pq.Len() > 1 {
		y := heap.Pop(pq).(int)
		x := heap.Pop(pq).(int)
		if y != x {
			heap.Push(pq, y-x)
		}
	}

	if pq.Len() == 0 {
		return 0
	}
	return pq.IntSlice[0]
}

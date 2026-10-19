package heaps

import (
	"container/heap"
	"sort"
)

type minHeap struct{ sort.IntSlice }

func (h *minHeap) Push(x any) { h.IntSlice = append(h.IntSlice, x.(int)) }

func (h *minHeap) Pop() any {
	old := h.IntSlice
	x := old[len(old)-1]
	h.IntSlice = old[:len(old)-1]
	return x
}

func findKthLargest(nums []int, k int) int {
	pq := &minHeap{}
	for _, x := range nums {
		if pq.Len() < k {
			heap.Push(pq, x)
		} else if x > pq.IntSlice[0] {
			pq.IntSlice[0] = x
			heap.Fix(pq, 0)
		}
	}
	return pq.IntSlice[0]
}

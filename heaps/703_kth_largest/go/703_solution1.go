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

type KthLargest struct {
	cap int
	pq  *minHeap
}

func Constructor(k int, nums []int) KthLargest {
	pq := &minHeap{nums}
	heap.Init(pq)
	for pq.Len() > k {
		heap.Pop(pq)
	}
	return KthLargest{cap: k, pq: pq}
}

func (this *KthLargest) Add(val int) int {
	heap.Push(this.pq, val)
	if this.pq.Len() > this.cap {
		heap.Pop(this.pq)
	}
	return this.pq.IntSlice[0]
}

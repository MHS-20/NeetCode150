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
	kl := KthLargest{cap: k, pq: &minHeap{}}
	for _, n := range nums {
		kl.Add(n)
	}
	return kl
}

func (this *KthLargest) Add(val int) int {
	if this.pq.Len() < this.cap {
		heap.Push(this.pq, val)
	} else if val > this.pq.IntSlice[0] {
		this.pq.IntSlice[0] = val
		heap.Fix(this.pq, 0)
	}
	return this.pq.IntSlice[0]
}

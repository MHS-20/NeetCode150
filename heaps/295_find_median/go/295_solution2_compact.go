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

func (h *minHeap) top() int { return h.IntSlice[0] }

type maxHeap struct{ minHeap }

func (h maxHeap) Less(i, j int) bool { return h.IntSlice[i] > h.IntSlice[j] }

type MedianFinder struct {
	lo *maxHeap // lower half
	hi *minHeap // upper half
}

func Constructor() MedianFinder {
	return MedianFinder{&maxHeap{}, &minHeap{}}
}

func (this *MedianFinder) AddNum(num int) {
	heap.Push(this.lo, num)
	heap.Push(this.hi, heap.Pop(this.lo))
	if this.hi.Len() > this.lo.Len() {
		heap.Push(this.lo, heap.Pop(this.hi))
	}
}

func (this *MedianFinder) FindMedian() float64 {
	if this.lo.Len() > this.hi.Len() {
		return float64(this.lo.top())
	}
	return float64(this.lo.top()+this.hi.top()) / 2
}

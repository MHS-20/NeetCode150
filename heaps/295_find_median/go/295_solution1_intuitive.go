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
	maxHeap *maxHeap // left half
	minHeap *minHeap // right half
}

func Constructor() MedianFinder {
	return MedianFinder{&maxHeap{}, &minHeap{}}
}

func (this *MedianFinder) AddNum(num int) {
	if this.minHeap.Len() > 0 && num >= this.minHeap.top() {
		heap.Push(this.minHeap, num)
	} else {
		heap.Push(this.maxHeap, num)
	}

	if this.maxHeap.Len() > this.minHeap.Len()+1 {
		heap.Push(this.minHeap, heap.Pop(this.maxHeap))
	}

	if this.minHeap.Len() > this.maxHeap.Len() {
		heap.Push(this.maxHeap, heap.Pop(this.minHeap))
	}
}

func (this *MedianFinder) FindMedian() float64 {
	if (this.minHeap.Len()+this.maxHeap.Len())%2 == 0 {
		return float64(this.minHeap.top()+this.maxHeap.top()) / 2
	}
	return float64(this.maxHeap.top())
}

package main

import "container/heap"

type minHeapItem struct {
	val, cnt int
}

type MinHeap []minHeapItem

func (h MinHeap) Len() int            { return len(h) }
func (h MinHeap) Less(i, j int) bool  { return h[i].cnt < h[j].cnt }
func (h MinHeap) Swap(i, j int)       { h[i], h[j] = h[j], h[i] }
func (h *MinHeap) Push(x interface{}) { *h = append(*h, x.(minHeapItem)) }
func (h *MinHeap) Pop() interface{} {
	old := *h
	n := len(old)
	item := old[n-1]
	*h = old[:n-1]
	return item
}

func topKFrequent(nums []int, k int) []int {
	freq := make(map[int]int)
	for _, n := range nums {
		freq[n]++
	}

	minHeap := &MinHeap{}
	heap.Init(minHeap)
	for val, cnt := range freq {
		heap.Push(minHeap, minHeapItem{val, cnt})
		if minHeap.Len() > k {
			heap.Pop(minHeap)
		}
	}

	res := make([]int, minHeap.Len())
	for i := len(res) - 1; i >= 0; i-- {
		res[i] = heap.Pop(minHeap).(minHeapItem).val
	}
	return res
}

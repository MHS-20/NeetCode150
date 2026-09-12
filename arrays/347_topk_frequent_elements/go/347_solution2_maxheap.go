package main

import "container/heap"

type maxHeapItem struct {
	val, cnt int
}

type MaxHeap []maxHeapItem

func (h MaxHeap) Len() int            { return len(h) }
func (h MaxHeap) Less(i, j int) bool  { return h[i].cnt > h[j].cnt }
func (h MaxHeap) Swap(i, j int)       { h[i], h[j] = h[j], h[i] }
func (h *MaxHeap) Push(x interface{}) { *h = append(*h, x.(maxHeapItem)) }
func (h *MaxHeap) Pop() interface{} {
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

	maxHeap := &MaxHeap{}
	heap.Init(maxHeap)
	for val, cnt := range freq {
		heap.Push(maxHeap, maxHeapItem{val, cnt})
	}

	res := make([]int, 0, k)
	for i := 0; i < k; i++ {
		res = append(res, heap.Pop(maxHeap).(maxHeapItem).val)
	}
	return res
}

package heaps

import "container/heap"

type entry struct {
	dist  int // squared distance, same order as the real one
	point []int
}

type maxHeap []entry

func (h maxHeap) Len() int           { return len(h) }
func (h maxHeap) Less(i, j int) bool { return h[i].dist > h[j].dist }
func (h maxHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *maxHeap) Push(x any)        { *h = append(*h, x.(entry)) }

func (h *maxHeap) Pop() any {
	old := *h
	x := old[len(old)-1]
	*h = old[:len(old)-1]
	return x
}

func kClosest(points [][]int, k int) [][]int {
	pq := &maxHeap{}

	for _, p := range points {
		heap.Push(pq, entry{p[0]*p[0] + p[1]*p[1], p})
		if pq.Len() > k {
			heap.Pop(pq)
		}
	}

	res := make([][]int, 0, k)
	for _, e := range *pq {
		res = append(res, e.point)
	}
	return res
}

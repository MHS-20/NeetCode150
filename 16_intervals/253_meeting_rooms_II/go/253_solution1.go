package intervals

import (
	"container/heap"
	"slices"
)

// Definition of Interval:
// type Interval struct {
//     start int
//     end   int
// }

type endHeap []int

func (h endHeap) Len() int           { return len(h) }
func (h endHeap) Less(i, j int) bool { return h[i] < h[j] }
func (h endHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *endHeap) Push(x any)        { *h = append(*h, x.(int)) }
func (h *endHeap) Pop() any {
	old := *h
	x := old[len(old)-1]
	*h = old[:len(old)-1]
	return x
}

func minMeetingRooms(intervals []Interval) int {
	mx := 0
	minHeap := &endHeap{}

	slices.SortFunc(intervals, func(a, b Interval) int { return a.start - b.start })

	for _, i := range intervals {
		for minHeap.Len() > 0 && (*minHeap)[0] <= i.start {
			heap.Pop(minHeap)
		}
		heap.Push(minHeap, i.end)
		mx = max(mx, minHeap.Len())
	}

	return mx
}

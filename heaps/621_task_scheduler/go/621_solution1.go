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

type cooldown struct{ count, nextTime int }

func leastInterval(tasks []byte, n int) int {
	var arr [26]int
	for _, ch := range tasks {
		arr[ch-'A']++
	}

	pq := &maxHeap{} // remaining counts
	for _, c := range arr {
		if c > 0 {
			pq.IntSlice = append(pq.IntSlice, c)
		}
	}
	heap.Init(pq)

	var timer []cooldown
	time := 0

	for pq.Len() > 0 || len(timer) > 0 {
		if len(timer) > 0 && timer[0].nextTime <= time {
			heap.Push(pq, timer[0].count)
			timer = timer[1:]
		}

		if pq.Len() > 0 {
			if count := heap.Pop(pq).(int) - 1; count > 0 {
				timer = append(timer, cooldown{count, time + n + 1})
			}
		}

		time++
	}

	return time
}

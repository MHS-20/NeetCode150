package linkedlists

import "container/heap"

type nodeHeap []*ListNode

func (h nodeHeap) Len() int           { return len(h) }
func (h nodeHeap) Less(i, j int) bool { return h[i].Val < h[j].Val }
func (h nodeHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *nodeHeap) Push(x any)        { *h = append(*h, x.(*ListNode)) }
func (h *nodeHeap) Pop() any {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[:n-1]
	return x
}

func mergeKLists(lists []*ListNode) *ListNode {
	minHeap := &nodeHeap{}

	// seed with the head of each non-empty list
	for _, head := range lists {
		if head != nil {
			*minHeap = append(*minHeap, head)
		}
	}
	heap.Init(minHeap)

	dummy := &ListNode{}
	cur := dummy

	for minHeap.Len() > 0 {
		smallest := heap.Pop(minHeap).(*ListNode)

		cur.Next = smallest
		cur = cur.Next

		// the only new candidate is the successor of the node we just took
		if smallest.Next != nil {
			heap.Push(minHeap, smallest.Next)
		}
	}

	return dummy.Next
}

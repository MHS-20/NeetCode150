package linkedlists

// slice of node pointers used as a deque (front index l, back index r)
func reorderListDeque(head *ListNode) {
	if head == nil || head.Next == nil {
		return
	}

	// 1. store every node
	var nodes []*ListNode
	for curr := head; curr != nil; curr = curr.Next {
		nodes = append(nodes, curr)
	}

	// 2. relink alternating between the front and the back
	l, r := 1, len(nodes)-1
	tail := head // nodes[0] is already the head
	for l <= r {
		tail.Next = nodes[r]
		tail = tail.Next
		r--
		if l <= r {
			tail.Next = nodes[l]
			tail = tail.Next
			l++
		}
	}
	tail.Next = nil
}

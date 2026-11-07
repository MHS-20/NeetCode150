package linkedlists

func reverseKGroup(head *ListNode, k int) *ListNode {
	// check that k nodes exist
	node := head
	for i := 0; i < k; i++ {
		if node == nil {
			return head // fewer than k: leave as is
		}
		node = node.Next
	}
	// node is now the (k+1)-th node, i.e. the start of the rest

	prev := reverseKGroup(node, k) // already-processed rest
	cur := head
	for i := 0; i < k; i++ {
		next := cur.Next
		cur.Next = prev
		prev = cur
		cur = next
	}
	return prev // new head of this group
}

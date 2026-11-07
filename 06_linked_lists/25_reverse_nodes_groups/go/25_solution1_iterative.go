package linkedlists

func reverseKGroup(head *ListNode, k int) *ListNode {
	dummy := &ListNode{Next: head}
	groupPrev := dummy

	for {
		// find the k-th node of this group
		kth := groupPrev
		for i := 0; i < k && kth != nil; i++ {
			kth = kth.Next
		}
		if kth == nil {
			break // fewer than k nodes left
		}

		groupStart := groupPrev.Next
		groupNext := kth.Next // first node after the group

		// reverse k nodes, starting with prev = groupNext so the
		// old head ends up pointing to the rest of the list
		prev := groupNext
		cur := groupStart
		for cur != groupNext {
			next := cur.Next
			cur.Next = prev
			prev = cur
			cur = next
		}

		groupPrev.Next = kth   // previous part -> new group head
		groupPrev = groupStart // old head is now the group's tail
	}

	return dummy.Next
}

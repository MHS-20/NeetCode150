package linkedlists

func removeNthFromEnd(head *ListNode, n int) *ListNode {
	dummy := &ListNode{Next: head}
	left := dummy
	right := dummy

	// create a gap of n nodes between left and right
	for i := 0; i < n; i++ {
		right = right.Next
	}

	// move both until right is on the last node;
	// left is then on the node before the target
	for right.Next != nil {
		right = right.Next
		left = left.Next
	}

	left.Next = left.Next.Next

	return dummy.Next
}

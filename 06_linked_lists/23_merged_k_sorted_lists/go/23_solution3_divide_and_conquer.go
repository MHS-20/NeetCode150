package linkedlists

func mergeTwo(a, b *ListNode) *ListNode {
	dummy := &ListNode{}
	cur := dummy
	for a != nil && b != nil {
		if a.Val <= b.Val {
			cur.Next = a
			a = a.Next
		} else {
			cur.Next = b
			b = b.Next
		}
		cur = cur.Next
	}
	if a != nil {
		cur.Next = a
	} else {
		cur.Next = b
	}
	return dummy.Next
}

func mergeKLists(lists []*ListNode) *ListNode {
	n := len(lists)
	if n == 0 {
		return nil
	}

	for step := 1; step < n; step *= 2 {
		for i := 0; i+step < n; i += 2 * step {
			lists[i] = mergeTwo(lists[i], lists[i+step])
		}
	}

	return lists[0]
}

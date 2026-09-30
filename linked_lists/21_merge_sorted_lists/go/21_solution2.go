package linkedlists

func mergeTwoLists(a *ListNode, b *ListNode) *ListNode {
	if a == nil {
		return b
	}
	if b == nil {
		return a
	}
	if a.Val <= b.Val {
		a.Next = mergeTwoLists(a.Next, b)
		return a
	}
	b.Next = mergeTwoLists(a, b.Next)
	return b
}

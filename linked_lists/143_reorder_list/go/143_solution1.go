package linkedlists

func reorderList(head *ListNode) {
	if head == nil || head.Next == nil {
		return
	}

	// 1. find the end of the first half
	slow, fast := head, head
	for fast.Next != nil && fast.Next.Next != nil {
		slow = slow.Next
		fast = fast.Next.Next
	}

	// 2. cut the list and reverse the second half
	var prev *ListNode
	curr := slow.Next
	slow.Next = nil // split into two lists

	for curr != nil {
		next := curr.Next
		curr.Next = prev
		prev = curr
		curr = next
	}
	second := prev // head of reversed second half

	// 3. merge: alternate nodes from first and second
	first := head
	for second != nil {
		next1, next2 := first.Next, second.Next

		first.Next = second
		second.Next = next1

		first, second = next1, next2
	}
}

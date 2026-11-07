package linkedlists

func reorderListStack(head *ListNode) {
	if head == nil || head.Next == nil {
		return
	}

	// 1. find the end of the first half
	slow, fast := head, head
	for fast.Next != nil && fast.Next.Next != nil {
		slow = slow.Next
		fast = fast.Next.Next
	}

	// 2. cut the list and push the second half onto a stack
	var stack []*ListNode
	for curr := slow.Next; curr != nil; curr = curr.Next {
		stack = append(stack, curr)
	}
	slow.Next = nil // split into two lists

	// 3. merge: popping the stack yields the second half in reverse
	first := head
	for len(stack) > 0 {
		second := stack[len(stack)-1]
		stack = stack[:len(stack)-1]

		second.Next = first.Next
		first.Next = second
		first = second.Next
	}
}

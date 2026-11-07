package linkedlists

func copyRandomListInterleaved(head *Node) *Node {
	if head == nil {
		return nil
	}

	// pass 1: interleave copies
	for cur := head; cur != nil; cur = cur.Next.Next {
		cur.Next = &Node{Val: cur.Val, Next: cur.Next}
	}

	// pass 2: set random pointers
	for cur := head; cur != nil; cur = cur.Next.Next {
		if cur.Random != nil {
			cur.Next.Random = cur.Random.Next
		}
	}

	// pass 3: separate the lists
	copyHead := head.Next
	for cur := head; cur != nil; cur = cur.Next {
		copy := cur.Next
		cur.Next = copy.Next
		if copy.Next != nil {
			copy.Next = copy.Next.Next
		}
	}

	return copyHead
}

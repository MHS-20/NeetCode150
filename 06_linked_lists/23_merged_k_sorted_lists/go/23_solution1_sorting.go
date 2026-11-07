package linkedlists

import "sort"

func mergeKLists(lists []*ListNode) *ListNode {
	// 1. collect every value from every list
	vals := []int{}
	for _, head := range lists {
		for p := head; p != nil; p = p.Next {
			vals = append(vals, p.Val)
		}
	}

	// 2. sort them
	sort.Ints(vals)

	// 3. rebuild a new list
	dummy := &ListNode{}
	cur := dummy
	for _, v := range vals {
		cur.Next = &ListNode{Val: v}
		cur = cur.Next
	}

	return dummy.Next
}

from list_node import ListNode


class Solution:
    def mergeTwoLists(self, a: ListNode, b: ListNode) -> ListNode:
        if not a:
            return b
        if not b:
            return a
        if a.val <= b.val:
            a.next = self.mergeTwoLists(a.next, b)
            return a
        b.next = self.mergeTwoLists(a, b.next)
        return b

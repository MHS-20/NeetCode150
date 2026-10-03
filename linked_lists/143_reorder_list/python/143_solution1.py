from typing import Optional

from list_node import ListNode


class Solution:
    def reorderList(self, head: Optional[ListNode]) -> None:
        if not head or not head.next:
            return

        # 1. find the end of the first half
        slow = fast = head
        while fast.next and fast.next.next:
            slow = slow.next
            fast = fast.next.next

        # 2. cut the list and reverse the second half
        prev = None
        curr = slow.next
        slow.next = None  # split into two lists

        while curr:
            curr.next, prev, curr = prev, curr, curr.next
        second = prev  # head of reversed second half

        # 3. merge: alternate nodes from first and second
        first = head
        while second:
            next1, next2 = first.next, second.next

            first.next = second
            second.next = next1

            first, second = next1, next2

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

        # 2. cut the list and push the second half onto a stack
        stack = []
        curr = slow.next
        while curr:
            stack.append(curr)
            curr = curr.next
        slow.next = None  # split into two lists

        # 3. merge: popping the stack yields the second half in reverse
        first = head
        while stack:
            second = stack.pop()
            second.next = first.next
            first.next = second
            first = second.next

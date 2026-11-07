from typing import Optional

from list_node import ListNode


class Solution:
    def removeNthFromEnd(
        self, head: Optional[ListNode], n: int
    ) -> Optional[ListNode]:
        dummy = ListNode(0, head)
        left = dummy
        right = dummy

        # create a gap of n nodes between left and right
        for _ in range(n):
            right = right.next

        # move both until right is on the last node;
        # left is then on the node before the target
        while right.next:
            right = right.next
            left = left.next

        left.next = left.next.next

        return dummy.next

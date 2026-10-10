from collections import deque
from typing import Optional

from list_node import ListNode


class Solution:
    def reorderList(self, head: Optional[ListNode]) -> None:
        if not head or not head.next:
            return

        # 1. store every node
        nodes = deque()
        curr = head
        while curr:
            nodes.append(curr)
            curr = curr.next

        # 2. relink alternating between the front and the back
        tail = nodes.popleft()  # the head stays first
        while nodes:
            tail.next = nodes.pop()
            tail = tail.next
            if nodes:
                tail.next = nodes.popleft()
                tail = tail.next
        tail.next = None

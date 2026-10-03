from typing import Optional

from node import Node


class Solution:
    def copyRandomList(self, head: Optional[Node]) -> Optional[Node]:
        copy_of = {None: None}  # None original -> None copy

        # pass 1: create all copies (no links yet)
        cur = head
        while cur:
            copy_of[cur] = Node(cur.val)
            cur = cur.next

        # pass 2: wire up next and random
        cur = head
        while cur:
            copy_of[cur].next = copy_of[cur.next]
            copy_of[cur].random = copy_of[cur.random]
            cur = cur.next

        return copy_of[head]

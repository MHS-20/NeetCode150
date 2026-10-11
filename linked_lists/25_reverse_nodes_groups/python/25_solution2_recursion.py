from typing import Optional

from list_node import ListNode


class Solution:
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        # check that k nodes exist
        node = head
        for _ in range(k):
            if not node:
                return head  # fewer than k: leave as is
            node = node.next
        # node is now the (k+1)-th node, i.e. the start of the rest

        prev = self.reverseKGroup(node, k)  # already-processed rest
        cur = head
        for _ in range(k):
            nxt = cur.next
            cur.next = prev
            prev = cur
            cur = nxt
        return prev  # new head of this group

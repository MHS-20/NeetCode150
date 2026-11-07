from typing import Optional

from list_node import ListNode


class Solution:
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        dummy = ListNode(0, head)
        group_prev = dummy

        while True:
            # find the k-th node of this group
            kth = group_prev
            for _ in range(k):
                if not kth:
                    break
                kth = kth.next
            if not kth:
                break  # fewer than k nodes left

            group_start = group_prev.next
            group_next = kth.next  # first node after the group

            # reverse k nodes, starting with prev = group_next so the
            # old head ends up pointing to the rest of the list
            prev = group_next
            cur = group_start
            while cur != group_next:
                nxt = cur.next
                cur.next = prev
                prev = cur
                cur = nxt

            group_prev.next = kth  # previous part -> new group head
            group_prev = group_start  # old head is now the group's tail

        return dummy.next

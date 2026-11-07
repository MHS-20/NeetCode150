from typing import List, Optional

from list_node import ListNode


class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        # 1. collect every value from every list
        vals = []
        for head in lists:
            while head:
                vals.append(head.val)
                head = head.next

        # 2. sort them
        vals.sort()

        # 3. rebuild a new list
        dummy = ListNode()
        cur = dummy
        for v in vals:
            cur.next = ListNode(v)
            cur = cur.next

        return dummy.next

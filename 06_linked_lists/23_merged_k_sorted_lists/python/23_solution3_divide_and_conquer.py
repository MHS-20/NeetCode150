from typing import List, Optional

from list_node import ListNode


class Solution:
    def _merge_two(self, a: Optional[ListNode], b: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode()
        cur = dummy
        while a and b:
            if a.val <= b.val:
                cur.next = a
                a = a.next
            else:
                cur.next = b
                b = b.next
            cur = cur.next
        cur.next = a if a else b
        return dummy.next

    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        n = len(lists)
        if n == 0:
            return None

        step = 1
        while step < n:
            for i in range(0, n - step, 2 * step):
                lists[i] = self._merge_two(lists[i], lists[i + step])
            step *= 2

        return lists[0]

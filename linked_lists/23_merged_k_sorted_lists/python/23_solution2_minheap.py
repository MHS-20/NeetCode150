import heapq
from typing import List, Optional

from list_node import ListNode


class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        # (val, index, node): the index breaks ties so nodes are never compared
        min_heap = [(head.val, i, head) for i, head in enumerate(lists) if head]
        heapq.heapify(min_heap)

        dummy = ListNode()
        cur = dummy

        while min_heap:
            _, i, smallest = heapq.heappop(min_heap)

            cur.next = smallest
            cur = cur.next

            # the only new candidate is the successor of the node we just took
            if smallest.next:
                heapq.heappush(min_heap, (smallest.next.val, i, smallest.next))

        return dummy.next

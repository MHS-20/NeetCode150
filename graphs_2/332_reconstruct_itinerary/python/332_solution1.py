import heapq
from collections import defaultdict
from typing import List


class Solution:
    def findItinerary(self, tickets: List[List[str]]) -> List[str]:
        adj = defaultdict(list)  # airport -> min-heap of destinations
        for frm, to in tickets:
            heapq.heappush(adj[frm], to)

        result = []

        def dfs(cur: str) -> None:
            dests = adj[cur]
            while dests:
                dfs(heapq.heappop(dests))  # use this ticket
            result.append(cur)  # post-order: no tickets left here

        dfs("JFK")
        return result[::-1]

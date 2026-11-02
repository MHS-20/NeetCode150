from collections import deque
from typing import List


class Solution:
    def findCheapestPrice(
        self, n: int, flights: List[List[int]], src: int, dst: int, k: int
    ) -> int:
        adj = [[] for _ in range(n)]  # from -> (to, price)
        for f, t, p in flights:
            adj[f].append((t, p))

        prices = [float("inf")] * n
        q = deque([(src, 0)])  # (city, cost so far)
        prices[src] = 0

        flights_used = 0
        # BFS by level, one level per flight (at most k + 1 levels)
        while flights_used <= k and q:
            for _ in range(len(q)):
                c, p = q.popleft()
                for nxt, price in adj[c]:
                    if p + price < prices[nxt]:
                        prices[nxt] = p + price
                        q.append((nxt, p + price))
            flights_used += 1

        return -1 if prices[dst] == float("inf") else prices[dst]

import heapq
from typing import List


class Solution:
    def networkDelayTime(self, times: List[List[int]], n: int, k: int) -> int:
        adj = [[] for _ in range(n + 1)]  # node -> (neighbor, weight)
        for u, v, w in times:
            adj[u].append((v, w))

        dist = [float("inf")] * (n + 1)
        dist[k] = 0
        pq = [(0, k)]  # (dist, node)

        while pq:
            d, u = heapq.heappop(pq)
            if d > dist[u]:
                continue  # stale entry
            for v, w in adj[u]:
                if d + w < dist[v]:
                    dist[v] = d + w
                    heapq.heappush(pq, (dist[v], v))

        ans = max(dist[1:])
        return -1 if ans == float("inf") else ans

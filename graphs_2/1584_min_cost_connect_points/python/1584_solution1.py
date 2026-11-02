from typing import List


class Solution:
    def minCostConnectPoints(self, points: List[List[int]]) -> int:
        n = len(points)
        min_cost = [float("inf")] * n
        in_tree = [False] * n
        min_cost[0] = 0
        cost = 0

        for _ in range(n):
            # 1. Pick the cheapest point not yet in the tree
            u = -1
            for i in range(n):
                if not in_tree[i] and (u == -1 or min_cost[i] < min_cost[u]):
                    u = i

            # 2. Add it
            in_tree[u] = True
            cost += min_cost[u]

            # 3. Update the outside points' best connection
            ux, uy = points[u]
            for i in range(n):
                if in_tree[i]:
                    continue
                dist = abs(points[i][0] - ux) + abs(points[i][1] - uy)
                min_cost[i] = min(min_cost[i], dist)

        return cost

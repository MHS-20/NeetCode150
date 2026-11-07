from typing import List


class Solution:
    def swimInWater(self, grid: List[List[int]]) -> int:
        n = len(grid)
        parent = list(range(n * n))
        rnk = [0] * (n * n)

        def find(x: int) -> int:
            while parent[x] != x:
                parent[x] = parent[parent[x]]  # path halving
                x = parent[x]
            return x

        def unite(a: int, b: int) -> None:
            a, b = find(a), find(b)
            if a == b:
                return
            if rnk[a] < rnk[b]:
                a, b = b, a
            parent[b] = a
            if rnk[a] == rnk[b]:
                rnk[a] += 1

        # pos[v] = cell index holding elevation v
        pos = [0] * (n * n)
        for r in range(n):
            for c in range(n):
                pos[grid[r][c]] = r * n + c

        for t in range(n * n):
            r, c = divmod(pos[t], n)  # this cell becomes submerged
            for dr, dc in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                nr, nc = r + dr, c + dc
                if nr < 0 or nc < 0 or nr >= n or nc >= n:
                    continue
                if grid[nr][nc] <= t:  # neighbor already submerged
                    unite(r * n + c, nr * n + nc)
            if find(0) == find(n * n - 1):
                return t
        return -1

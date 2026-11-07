from collections import deque
from typing import List


class Solution:
    def swimInWater(self, grid: List[List[int]]) -> int:
        n = len(grid)

        def can_reach(t: int) -> bool:
            if grid[0][0] > t:
                return False
            visited = [[False] * n for _ in range(n)]
            q = deque([(0, 0)])
            visited[0][0] = True

            while q:
                r, c = q.popleft()
                if r == n - 1 and c == n - 1:
                    return True
                for dr, dc in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                    nr, nc = r + dr, c + dc
                    if nr < 0 or nc < 0 or nr >= n or nc >= n:
                        continue
                    if visited[nr][nc] or grid[nr][nc] > t:
                        continue
                    visited[nr][nc] = True
                    q.append((nr, nc))
            return False

        lo, hi = 0, n * n - 1
        while lo < hi:
            mid = (lo + hi) // 2
            if can_reach(mid):
                hi = mid  # works: try lower
            else:
                lo = mid + 1  # fails: need more water
        return lo

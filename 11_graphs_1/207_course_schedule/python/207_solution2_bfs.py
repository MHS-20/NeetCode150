from collections import deque
from typing import List


class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        unlocks: List[List[int]] = [[] for _ in range(numCourses)]  # b -> courses that need b
        remaining = [0] * numCourses  # prerequisites still missing

        for a, b in prerequisites:
            unlocks[b].append(a)
            remaining[a] += 1

        q = deque(c for c in range(numCourses) if remaining[c] == 0)

        taken = 0
        while q:
            c = q.popleft()
            taken += 1

            for nxt in unlocks[c]:
                remaining[nxt] -= 1
                if remaining[nxt] == 0:
                    q.append(nxt)

        return taken == numCourses

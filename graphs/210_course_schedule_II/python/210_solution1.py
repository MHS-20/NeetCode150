from typing import List


class Solution:
    def findOrder(self, numCourses: int, prerequisites: List[List[int]]) -> List[int]:
        adjacency: List[List[int]] = [[] for _ in range(numCourses)]
        for course, pre in prerequisites:
            adjacency[course].append(pre)

        state = [0] * numCourses  # 0 = unvisited, 1 = on path, 2 = done
        order: List[int] = []

        def dfs(node: int) -> bool:
            if state[node] == 1:
                return False  # cycle
            if state[node] == 2:
                return True

            state[node] = 1
            for nxt in adjacency[node]:
                if not dfs(nxt):
                    return False
            state[node] = 2
            order.append(node)
            return True

        if not all(dfs(i) for i in range(numCourses)):
            return []
        return order

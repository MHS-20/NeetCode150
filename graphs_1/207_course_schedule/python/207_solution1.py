from typing import List


class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        adjacency: List[List[int]] = [[] for _ in range(numCourses)]
        for course, pre in prerequisites:
            adjacency[course].append(pre)

        state = [0] * numCourses  # 0 = unvisited, 1 = on path, 2 = done

        def dfs(node: int) -> bool:
            if state[node] == 1:
                return False  # back on the current path: cycle
            if state[node] == 2:
                return True  # already fully explored

            state[node] = 1
            for nxt in adjacency[node]:
                if not dfs(nxt):
                    return False
            state[node] = 2
            return True

        return all(dfs(i) for i in range(numCourses))

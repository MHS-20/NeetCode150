from typing import List


class Solution:
    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:
        result: List[List[int]] = []
        cur: List[int] = []
        candidates.sort()

        def backtrack(idx: int, total: int) -> None:
            if total == target:
                result.append(cur[:])
                return

            if total > target or idx == len(candidates):
                return

            cur.append(candidates[idx])
            backtrack(idx + 1, total + candidates[idx])
            cur.pop()

            i = idx + 1
            while i < len(candidates) and candidates[i] == candidates[idx]:
                i += 1
            backtrack(i, total)

        backtrack(0, 0)
        return result

from typing import List


class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        result: List[List[int]] = []
        cur: List[int] = []

        def backtrack(idx: int, total: int) -> None:
            if total == target:
                result.append(cur[:])
                return
            if total > target or idx >= len(candidates):
                return

            # include candidates[idx], stay on idx (can reuse it)
            cur.append(candidates[idx])
            backtrack(idx, total + candidates[idx])
            cur.pop()

            # skip candidates[idx] for good, move on
            backtrack(idx + 1, total)

        backtrack(0, 0)
        return result

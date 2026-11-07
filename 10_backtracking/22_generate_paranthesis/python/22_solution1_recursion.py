from typing import List


class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        res = []

        def build(opened: int, closed: int, cur: str) -> None:
            if closed == n:  # implies opened == n too
                res.append(cur)
                return
            if opened < n:
                build(opened + 1, closed, cur + "(")
            if closed < opened:
                build(opened, closed + 1, cur + ")")

        build(0, 0, "")
        return res

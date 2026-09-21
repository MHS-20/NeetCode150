from typing import List


class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        res = []
        cur = []

        def backtrack(opened: int, closed: int) -> None:
            if closed == n:  # implies opened == n too
                res.append("".join(cur))  # joins once, only for finished answers
                return

            if opened < n:
                cur.append("(")  # choose
                backtrack(opened + 1, closed)  # explore
                cur.pop()  # undo

            if closed < opened:
                cur.append(")")
                backtrack(opened, closed + 1)
                cur.pop()

        backtrack(0, 0)
        return res

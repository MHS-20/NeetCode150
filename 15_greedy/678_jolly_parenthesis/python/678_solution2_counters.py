class Solution:
    # hi is the count if every * is a '('. If even that drops below 0, there's an
    # unmatched ')' no matter what. lo is the count if every * is a ')'. Clamping
    # it to 0 throws away choices that would close more than is open.
    def checkValidString(self, s: str) -> bool:
        lo = hi = 0  # min and max possible number of open '('

        for c in s:
            if c == "(":
                lo += 1
                hi += 1
            elif c == ")":
                lo -= 1
                hi -= 1
            else:  # '*' could be ')' or '('
                lo -= 1
                hi += 1

            if hi < 0:
                return False  # too many ')', even with every '*' as '('
            lo = max(lo, 0)  # the count can't go negative, so drop those choices

        return lo == 0  # some choice of '*' leaves zero open

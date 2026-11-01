class Solution:
    def checkValidString(self, s: str) -> bool:
        open_, star = [], []  # indices of unmatched '(' and '*'

        for i, c in enumerate(s):
            if c == "(":
                open_.append(i)
            elif c == "*":
                star.append(i)
            elif open_:
                open_.pop()
            elif star:
                star.pop()
            else:
                return False

        # each leftover '(' needs a later '*' to close it
        while open_:
            if not star or star[-1] < open_[-1]:
                return False
            open_.pop()
            star.pop()
        return True

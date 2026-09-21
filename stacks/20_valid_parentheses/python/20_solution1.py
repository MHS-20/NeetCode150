class Solution:
    def isValid(self, s: str) -> bool:
        expected = []  # closing brackets we still owe
        closer = {"(": ")", "[": "]", "{": "}"}

        for c in s:
            if c in closer:
                expected.append(closer[c])
            elif not expected or expected.pop() != c:
                return False
        return not expected

from collections import defaultdict


class Solution:
    def checkInclusion(self, s1: str, s2: str) -> bool:
        k = len(s1)
        diff = defaultdict(int)
        mismatched = 0

        # shift a letter's diff by delta, keeping `mismatched` in sync
        def update(c, delta):
            nonlocal mismatched
            if diff[c] == 0:
                mismatched += 1  # was balanced, about to break
            diff[c] += delta
            if diff[c] == 0:
                mismatched -= 1  # now balanced again

        for c in s1:
            update(c, -1)

        for right in range(len(s2)):
            update(s2[right], 1)  # char enters
            if right >= k:
                update(s2[right - k], -1)  # char leaves
            if mismatched == 0:
                return True
        return False

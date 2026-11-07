from collections import Counter, defaultdict


class Solution:
    def checkInclusion(self, s1: str, s2: str) -> bool:
        k = len(s1)
        freq = Counter(s1)
        wfreq = defaultdict(int)

        need = len(freq)  # distinct letters in s1, fixed from here on
        matches = 0  # letters of s1 whose window count equals freq

        # change the window count of c by delta, keeping `matches` in sync
        def update(c, delta):
            nonlocal matches
            if c not in freq:
                return  # not in s1: irrelevant
            if wfreq[c] == freq[c]:
                matches -= 1  # was matching, about to change
            wfreq[c] += delta
            if wfreq[c] == freq[c]:
                matches += 1  # matches now

        for right in range(len(s2)):
            update(s2[right], 1)  # char enters
            if right >= k:
                update(s2[right - k], -1)  # char leaves
            if matches == need:
                return True
        return False

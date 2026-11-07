class Solution:
    def checkInclusion(self, s1: str, s2: str) -> bool:
        k = len(s1)
        freq = [0] * 26
        wfreq = [0] * 26
        for c in s1:
            freq[ord(c) - ord("a")] += 1

        # matches = number of the 26 letters whose window count equals freq
        # empty window: letters absent from s1 already match
        matches = sum(f == 0 for f in freq)

        # change the window count of a letter by delta, keeping `matches` in sync
        def update(ch, delta):
            nonlocal matches
            c = ord(ch) - ord("a")
            if wfreq[c] == freq[c]:
                matches -= 1  # was matching, about to change
            wfreq[c] += delta
            if wfreq[c] == freq[c]:
                matches += 1  # matches now

        for right in range(len(s2)):
            update(s2[right], 1)  # char enters
            if right >= k:
                update(s2[right - k], -1)  # char leaves
            if matches == 26:
                return True
        return False

class Solution:
    def checkInclusion(self, s1: str, s2: str) -> bool:
        if len(s1) > len(s2):
            return False

        s1freq = [0] * 26
        windowfreq = [0] * 26
        for i in range(len(s1)):
            s1freq[ord(s1[i]) - ord("a")] += 1
            windowfreq[ord(s2[i]) - ord("a")] += 1

        match = sum(a == b for a, b in zip(s1freq, windowfreq))
        if match == 26:
            return True

        left = 0
        for right in range(len(s1), len(s2)):
            r = ord(s2[right]) - ord("a")
            l = ord(s2[left]) - ord("a")

            # add right char
            if windowfreq[r] == s1freq[r]:
                match -= 1
            windowfreq[r] += 1
            if windowfreq[r] == s1freq[r]:
                match += 1

            # remove left char
            if windowfreq[l] == s1freq[l]:
                match -= 1
            windowfreq[l] -= 1
            if windowfreq[l] == s1freq[l]:
                match += 1

            left += 1
            if match == 26:
                return True
        return False

class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        reps = {}
        left = 0
        max_len = k
        max_freq = 0

        for right, c in enumerate(s):
            reps[c] = reps.get(c, 0) + 1
            max_freq = max(max_freq, reps[c])

            if right - left - max_freq >= k:
                reps[s[left]] -= 1
                left += 1

            max_len = max(max_len, right - left + 1)

        return max_len

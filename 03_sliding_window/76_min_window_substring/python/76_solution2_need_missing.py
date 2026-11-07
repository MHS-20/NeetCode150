class Solution:
    def minWindow(self, s: str, t: str) -> str:
        need = [0] * 128
        for c in t:
            need[ord(c)] += 1
        missing = len(t)

        best_start, best_len = 0, float("inf")
        left = 0

        for right, c in enumerate(s):
            if need[ord(c)] > 0:
                missing -= 1  # this char was still needed
            need[ord(c)] -= 1

            while missing == 0:  # window is valid: try to shrink
                if right - left + 1 < best_len:
                    best_start, best_len = left, right - left + 1
                need[ord(s[left])] += 1
                if need[ord(s[left])] > 0:
                    missing += 1  # we just removed a needed char
                left += 1

        return "" if best_len == float("inf") else s[best_start : best_start + best_len]

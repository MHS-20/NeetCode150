from collections import Counter


class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        # Python iterates str by Unicode code point already, so this is
        # unicode-safe by default (unlike C++'s byte-oriented std::string).
        return Counter(s) == Counter(t)

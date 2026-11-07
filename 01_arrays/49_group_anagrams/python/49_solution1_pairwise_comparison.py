from collections import Counter


class Solution:
    def groupAnagrams(self, strs: list[str]) -> list[list[str]]:
        result = []

        for s in strs:
            placed = False
            for group in result:
                if self.isAnagram(s, group[0]):
                    group.append(s)
                    placed = True
                    break

            if not placed:
                result.append([s])

        return result

    def isAnagram(self, s: str, t: str) -> bool:
        return Counter(s) == Counter(t)

from collections import defaultdict


class Solution:
    def groupAnagrams(self, strs: list[str]) -> list[list[str]]:
        groups = defaultdict(list)

        for s in strs:
            key = self.serializeFrequency(s)
            groups[key].append(s)

        return list(groups.values())

    def serializeFrequency(self, s: str) -> str:
        alphabet = [0] * 26
        for c in s:
            alphabet[ord(c) - ord("a")] += 1

        return "#".join(map(str, alphabet))

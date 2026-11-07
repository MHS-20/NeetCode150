from collections import Counter
from typing import List


class Solution:
    def isNStraightHand(self, hand: List[int], groupSize: int) -> bool:
        if len(hand) % groupSize != 0:
            return False

        count = Counter(hand)

        # ascending, so each value is the smallest remaining card when reached
        for start in sorted(count):
            c = count[start]
            if c == 0:
                continue  # already used up by earlier groups
            for v in range(start, start + groupSize):
                if count.get(v, 0) < c:
                    return False  # missing value, group can't be built
                count[v] -= c

        return True

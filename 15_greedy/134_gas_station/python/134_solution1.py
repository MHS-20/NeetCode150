from typing import List


class Solution:
    def canCompleteCircuit(self, gas: List[int], cost: List[int]) -> int:
        if sum(cost) > sum(gas):
            return -1

        start = cur_gas = cur_pos = 0
        while True:
            cur_gas += gas[cur_pos] - cost[cur_pos]

            cur_pos = (cur_pos + 1) % len(gas)

            if cur_pos == start:
                return start

            if cur_gas < 0:
                start = cur_pos
                cur_gas = 0

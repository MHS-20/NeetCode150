from typing import List


class Solution:
    def findCheapestPrice(self, n: int, flights: List[List[int]], src: int, dst: int, k: int) -> int:
        prices = [float("inf")] * n
        prices[src] = 0

        # Bellman-Ford limited to k + 1 rounds: round i allows i flights
        for _ in range(k + 1):
            nxt = prices[:]  # reads come from the previous round only
            for frm, to, price in flights:
                if prices[frm] + price < nxt[to]:
                    nxt[to] = prices[frm] + price
            prices = nxt

        return -1 if prices[dst] == float("inf") else prices[dst]

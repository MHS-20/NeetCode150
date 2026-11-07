import heapq
from collections import Counter, deque
from typing import List


class Solution:
    def leastInterval(self, tasks: List[str], n: int) -> int:
        pq = [-c for c in Counter(tasks).values()]  # negate for a max-heap
        heapq.heapify(pq)

        timer = deque()  # (count, next_time)
        time = 0

        while pq or timer:
            if timer and timer[0][1] <= time:
                heapq.heappush(pq, -timer.popleft()[0])

            if pq:
                count = -heapq.heappop(pq) - 1
                if count > 0:
                    timer.append((count, time + n + 1))

            time += 1

        return time

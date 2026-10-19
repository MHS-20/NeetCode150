import heapq
from collections import defaultdict
from typing import List


class Twitter:
    def __init__(self):
        self.timestamp = 0
        self.tweets: dict[int, list[tuple[int, int]]] = defaultdict(list)  # userId -> (timestamp, tweetId)
        self.following: dict[int, set[int]] = defaultdict(set)  # userId -> followeeIds

    def postTweet(self, userId: int, tweetId: int) -> None:
        self.tweets[userId].append((self.timestamp, tweetId))
        self.timestamp += 1

    def getNewsFeed(self, userId: int) -> List[int]:
        # min-heap of size 10, ordered by timestamp: top is the oldest of the kept tweets
        pq: list[tuple[int, int]] = []

        def scan(uid: int) -> None:
            for t in self.tweets.get(uid, []):
                heapq.heappush(pq, t)
                if len(pq) > 10:
                    heapq.heappop(pq)

        scan(userId)
        for f in self.following.get(userId, ()):
            if f != userId:
                scan(f)  # avoid scanning own tweets twice

        # heap pops oldest first, so reverse at the end
        res = [heapq.heappop(pq)[1] for _ in range(len(pq))]
        return res[::-1]

    def follow(self, followerId: int, followeeId: int) -> None:
        self.following[followerId].add(followeeId)

    def unfollow(self, followerId: int, followeeId: int) -> None:
        self.following[followerId].discard(followeeId)

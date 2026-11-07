import heapq
from collections import defaultdict
from typing import List


class Twitter:
    def __init__(self):
        self.timestamp = 0  # global counter, += 1 on every postTweet
        self.tweets: dict[int, list[tuple[int, int]]] = defaultdict(list)  # userId -> list of (timestamp, tweetId)
        self.following: dict[int, set[int]] = defaultdict(set)  # userId -> set of followeeIds

    def postTweet(self, userId: int, tweetId: int) -> None:
        self.tweets[userId].append((self.timestamp, tweetId))
        self.timestamp += 1

    def getNewsFeed(self, userId: int) -> List[int]:
        pq = []  # (-time, tweetId, user, idx): negate for a max-heap
        res = []

        for user in self.following.get(userId, set()) | {userId}:
            if self.tweets.get(user):
                idx = len(self.tweets[user]) - 1
                time, tweet_id = self.tweets[user][idx]
                pq.append((-time, tweet_id, user, idx))
        heapq.heapify(pq)

        while pq and len(res) < 10:
            _, tweet_id, user, idx = heapq.heappop(pq)
            res.append(tweet_id)
            if idx > 0:
                time, tweet_id = self.tweets[user][idx - 1]
                heapq.heappush(pq, (-time, tweet_id, user, idx - 1))

        return res

    def follow(self, followerId: int, followeeId: int) -> None:
        self.following[followerId].add(followeeId)

    def unfollow(self, followerId: int, followeeId: int) -> None:
        self.following[followerId].discard(followeeId)

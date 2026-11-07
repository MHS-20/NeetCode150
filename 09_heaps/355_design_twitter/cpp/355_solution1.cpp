#include <functional>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

class Twitter {
private:
  int timestamp = 0;
  unordered_map<int, vector<pair<int, int>>>
      tweets; // userId -> {timestamp, tweetId}
  unordered_map<int, unordered_set<int>> following; // userId -> followeeIds

public:
  Twitter() {}

  void postTweet(int userId, int tweetId) {
    tweets[userId].push_back({timestamp++, tweetId});
  }

  vector<int> getNewsFeed(int userId) {
    // min-heap of size 10, ordered by timestamp: top is the oldest of the kept
    // tweets
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    auto scan = [&](int uid) {
      auto it = tweets.find(uid);
      if (it == tweets.end())
        return;
      for (auto &t : it->second) {
        pq.push(t);
        if (pq.size() > 10)
          pq.pop();
      }
    };

    scan(userId);
    for (int f : following[userId]) {
      if (f != userId)
        scan(f); // avoid scanning own tweets twice
    }

    // heap pops oldest first, so fill the result from the back
    vector<int> res(pq.size());
    for (int i = (int)pq.size() - 1; i >= 0; i--) {
      res[i] = pq.top().second;
      pq.pop();
    }
    return res;
  }

  void follow(int followerId, int followeeId) {
    following[followerId].insert(followeeId);
  }

  void unfollow(int followerId, int followeeId) {
    following[followerId].erase(followeeId);
  }
};

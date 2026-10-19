#include <array>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

class Twitter {
private:
  int timestamp = 0; // global counter, ++ on every postTweet
  unordered_map<int, vector<pair<int, int>>>
      tweets; // userId -> list of {timestamp, tweetId}
  unordered_map<int, unordered_set<int>>
      following; // userId -> set of followeeIds

public:
  Twitter() {}

  void postTweet(int userId, int tweetId) {
    tweets[userId].push_back({timestamp++, tweetId});
  }

  vector<int> getNewsFeed(int userId) {
    priority_queue<array<int, 4>> pq;
    vector<int> res;

    auto users = following[userId];
    users.insert(userId);

    for (int user : users) {
      if (!tweets[user].empty()) {
        int idx = tweets[user].size() - 1;
        auto [time, tweetid] = tweets[user].back();
        pq.push({time, tweetid, user, idx});
      }
    }

    while (!pq.empty() && res.size() < 10) {
      auto [time, tweetid, user, idx] = pq.top();
      pq.pop();
      res.push_back(tweetid);
      if (idx > 0) {
        auto [ntime, ntweetid] = tweets[user][idx - 1];
        pq.push({ntime, ntweetid, user, idx - 1});
      }
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

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */

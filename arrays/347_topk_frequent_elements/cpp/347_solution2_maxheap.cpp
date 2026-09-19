#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
  vector<int> topKFrequent(vector<int> &nums, int k) {
    unordered_map<int, int> freq;
    priority_queue<pair<int, int>> pq;
    vector<int> res;

    for (int &n : nums)
      freq[n]++;

    for (auto it : freq)
      pq.push({it.second, it.first});

    for (int i = 0; i < k; i++) {
      res.push_back(pq.top().second);
      pq.pop();
    }

    return res;
  }
};

#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
  vector<int> topKFrequent(vector<int> &nums, int k) {
    unordered_map<int, int> freq;
    for (int &n : nums)
      freq[n]++;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
    for (auto &[val, cnt] : freq) {
      minHeap.push({cnt, val});
      if (minHeap.size() > k)
        minHeap.pop();
    }

    vector<int> res;
    while (!minHeap.empty()) {
      res.push_back(minHeap.top().second);
      minHeap.pop();
    }
    return res;
  }
};

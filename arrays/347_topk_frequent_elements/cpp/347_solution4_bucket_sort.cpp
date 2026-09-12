#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
  vector<int> topKFrequent(vector<int> &nums, int k) {
    unordered_map<int, int> freq;
    for (int &n : nums)
      freq[n]++;

    vector<vector<int>> buckets(nums.size() + 1);
    for (auto &f : freq)
      buckets[f.second].push_back(f.first);

    vector<int> res;
    for (int i = buckets.size() - 1; i >= 0 && (int)res.size() < k; i--) {
      for (int val : buckets[i]) {
        res.push_back(val);
        if ((int)res.size() == k)
          break;
      }
    }

    return res;
  }
};

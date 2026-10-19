#include <functional>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
  int findKthLargest(vector<int> &nums, int k) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int x : nums) {
      if ((int)pq.size() < k)
        pq.push(x);
      else if (x > pq.top()) {
        pq.pop();
        pq.push(x);
      }
    }
    return pq.top();
  }
};

#include <functional>
#include <queue>
#include <vector>

using namespace std;

class KthLargest {
private:
  int cap;
  priority_queue<int, vector<int>, greater<int>> pq;

public:
  KthLargest(int k, vector<int> &nums) : cap(k), pq(nums.begin(), nums.end()) {
    while (pq.size() > cap)
      pq.pop();
  }

  int add(int val) {
    pq.push(val);
    if (pq.size() > cap)
      pq.pop();
    return pq.top();
  }
};

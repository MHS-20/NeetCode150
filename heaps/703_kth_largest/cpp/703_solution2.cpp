#include <functional>
#include <queue>
#include <vector>

using namespace std;

class KthLargest {
private:
  int cap;
  priority_queue<int, vector<int>, greater<int>> pq;

public:
  KthLargest(int k, vector<int> &nums) : cap(k) {
    for (int n : nums)
      add(n);
  }

  int add(int val) {
    if (pq.size() < cap) {
      pq.push(val);
    } else if (val > pq.top()) {
      pq.pop();
      pq.push(val);
    }
    return pq.top();
  }
};

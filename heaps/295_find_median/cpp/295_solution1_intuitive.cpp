#include <functional>
#include <queue>
#include <vector>

using namespace std;

class MedianFinder {
private:
  priority_queue<int> maxHeap;                            // left half
  priority_queue<int, vector<int>, greater<int>> minHeap; // right half
public:
  MedianFinder() {}

  void addNum(int num) {
    if (!minHeap.empty() && num >= minHeap.top())
      minHeap.push(num);
    else
      maxHeap.push(num);

    if (maxHeap.size() > minHeap.size() + 1) {
      minHeap.push(maxHeap.top());
      maxHeap.pop();
    }

    if (minHeap.size() > maxHeap.size()) {
      maxHeap.push(minHeap.top());
      minHeap.pop();
    }
  }

  double findMedian() {
    if ((minHeap.size() + maxHeap.size()) % 2 == 0)
      return (minHeap.top() + maxHeap.top()) / 2.0;
    else
      return maxHeap.top();
  }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

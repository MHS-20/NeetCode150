#include <queue>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
  int leastInterval(vector<char> &tasks, int n) {
    int time = 0;
    int arr[26] = {};

    queue<pair<int, int>> timer;
    priority_queue<pair<int, int>> pq;

    for (char ch : tasks)
      arr[ch - 'A']++;

    for (int i = 0; i < 26; i++) {
      if (arr[i] > 0)
        pq.push({arr[i], i});
    }

    while (!pq.empty() || !timer.empty()) {
      if (!timer.empty()) {
        auto [index, nextTime] = timer.front();
        if (nextTime <= time) {
          pq.push({arr[index], index});
          timer.pop();
        }
      }

      if (!pq.empty()) {
        auto [count, index] = pq.top();
        pq.pop();
        arr[index]--;

        if (arr[index] > 0)
          timer.push({index, time + n + 1});
      }

      time++;
    }

    return time;
  }
};

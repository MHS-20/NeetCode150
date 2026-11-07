#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

class TimeMap {
private:
  unordered_map<string, vector<pair<int, string>>> kv;

public:
  TimeMap() {}

  void set(string key, string value, int timestamp) {
    kv[key].push_back({timestamp, value});
  }

  string get(string key, int timestamp) {
    if (!kv.count(key))
      return "";

    auto &arr = kv[key];
    int left = 0, right = arr.size() - 1, resIdx = -1;

    while (left <= right) {
      int mid = left + (right - left) / 2;

      if (arr[mid].first == timestamp)
        return arr[mid].second;

      if (arr[mid].first > timestamp)
        right = mid - 1;
      else {
        resIdx = mid;
        left = mid + 1;
      }
    }

    return resIdx == -1 ? "" : arr[resIdx].second;
  }
};

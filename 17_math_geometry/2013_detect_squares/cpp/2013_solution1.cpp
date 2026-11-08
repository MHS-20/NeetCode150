#include <cstdlib>
#include <map>
#include <utility>
#include <vector>

using namespace std;

class DetectSquares {
  map<pair<int, int>, int> cnt;

  int get(int x, int y) {
    auto it = cnt.find({x, y});
    return it == cnt.end() ? 0 : it->second;
  }

public:
  DetectSquares() {}

  void add(vector<int> point) { cnt[{point[0], point[1]}]++; }

  int count(vector<int> point) {
    int x = point[0], y = point[1], res = 0;

    for (auto &[p, c] : cnt) {
      int px = p.first, py = p.second;
      if (px == x || abs(px - x) != abs(py - y))
        continue; // must be a diagonal corner with side length > 0
      res += c * get(x, py) * get(px, y);
    }
    return res;
  }
};

#include <algorithm>
#include <stack>
#include <vector>
using namespace std;

class Solution {
public:
  int carFleet(int target, vector<int> &position, vector<int> &speed) {
    stack<float> st;
    vector<pair<int, int>> cars;

    for (int i = 0; i < position.size(); i++)
      cars.push_back({position[i], speed[i]});
    sort(cars.begin(), cars.end());

    for (int i = cars.size() - 1; i >= 0; i--) {
      float hours = (target - cars[i].first) / (float)cars[i].second;
      if (!st.empty()) {
        if (hours > st.top())
          st.push(hours);
      } else
        st.push(hours);
    }

    return st.size();
  }
};

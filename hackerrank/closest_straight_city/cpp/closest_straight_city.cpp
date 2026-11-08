#include <bits/stdc++.h>
using namespace std;

vector<string> closestStraightCity(const vector<string> &names,
                                   const vector<int> &x, const vector<int> &y) {
  int n = names.size();
  unordered_map<int, vector<int>> byX, byY; // coordinate -> city indices
  for (int i = 0; i < n; ++i) {
    byX[x[i]].push_back(i);
    byY[y[i]].push_back(i);
  }

  vector<long long> bestDist(n, LLONG_MAX);
  vector<int> bestIdx(n, -1);

  auto consider = [&](int i, int j) {
    long long d = llabs((long long)x[i] - x[j]) + llabs((long long)y[i] - y[j]);
    if (d < bestDist[i] || (d == bestDist[i] && names[j] < names[bestIdx[i]])) {
      bestDist[i] = d;
      bestIdx[i] = j;
    }
  };

  // Same x: sort by y, check adjacent cities
  for (auto &[_, v] : byX) {
    sort(v.begin(), v.end(), [&](int a, int b) { return y[a] < y[b]; });
    for (int k = 0; k + 1 < (int)v.size(); ++k) {
      consider(v[k], v[k + 1]);
      consider(v[k + 1], v[k]);
    }
  }
  // Same y: sort by x, check adjacent cities
  for (auto &[_, v] : byY) {
    sort(v.begin(), v.end(), [&](int a, int b) { return x[a] < x[b]; });
    for (int k = 0; k + 1 < (int)v.size(); ++k) {
      consider(v[k], v[k + 1]);
      consider(v[k + 1], v[k]);
    }
  }

  vector<string> res(n);
  for (int i = 0; i < n; ++i)
    res[i] = bestIdx[i] == -1 ? "NONE" : names[bestIdx[i]];
  return res;
}

int main() {
  vector<string> names = {"c1", "c2", "c3"};
  vector<int> x = {3, 2, 1};
  vector<int> y = {3, 2, 3};
  for (auto &s : closestStraightCity(names, x, y))
    cout << s << "\n";
  // c3, NONE, c1
}

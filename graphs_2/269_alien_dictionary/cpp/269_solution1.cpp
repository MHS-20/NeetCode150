#include <algorithm>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  string foreignDictionary(vector<string> &words) {
    bool seen[26] = {};
    bool edge[26][26] = {};
    int indeg[26] = {};
    int total = 0;

    // 1. Register every letter that appears
    for (auto &w : words)
      for (char c : w)
        if (!seen[c - 'a']) {
          seen[c - 'a'] = true;
          total++;
        }

    // 2. Build edges from adjacent word pairs
    for (int i = 0; i + 1 < (int)words.size(); i++) {
      const string &a = words[i];
      const string &b = words[i + 1];
      auto [it1, it2] = mismatch(a.begin(), a.end(), b.begin(), b.end());

      if (it1 == a.end())
        continue; // a is prefix of b (or equal): fine
      if (it2 == b.end())
        return ""; // b is a proper prefix of a: invalid

      int u = *it1 - 'a', v = *it2 - 'a';
      if (!edge[u][v]) { // avoid double-counting
        edge[u][v] = true;
        indeg[v]++;
      }
    }

    // 3. Kahn's algorithm
    queue<int> q;
    for (int c = 0; c < 26; c++)
      if (seen[c] && indeg[c] == 0)
        q.push(c);

    string result;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      result += char('a' + u);
      for (int v = 0; v < 26; v++) {
        if (edge[u][v] && --indeg[v] == 0)
          q.push(v);
      }
    }

    // 4. Cycle check
    return (int)result.size() == total ? result : "";
  }
};

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution {
  bool seen[26] = {};
  bool edge[26][26] = {};
  int state[26] = {}; // 0 = unvisited, 1 = visiting, 2 = done
  string result;

  // Returns false if a cycle is found
  bool dfs(int u) {
    state[u] = 1;
    for (int v = 0; v < 26; v++) {
      if (!edge[u][v])
        continue;
      if (state[v] == 1)
        return false; // back edge: cycle
      if (state[v] == 0 && !dfs(v))
        return false; // propagate failure
    }
    state[u] = 2;
    result += char('a' + u); // post-order
    return true;
  }

public:
  string foreignDictionary(vector<string> &words) {
    // 1. Register every letter
    for (auto &w : words)
      for (char c : w)
        seen[c - 'a'] = true;

    // 2. Build edges (no in-degree needed)
    for (int i = 0; i + 1 < (int)words.size(); i++) {
      const string &a = words[i];
      const string &b = words[i + 1];
      auto [it1, it2] = mismatch(a.begin(), a.end(), b.begin(), b.end());

      if (it1 == a.end())
        continue;
      if (it2 == b.end())
        return "";

      edge[*it1 - 'a'][*it2 - 'a'] = true; // duplicates are harmless here
    }

    // 3. DFS from every unvisited letter
    for (int c = 0; c < 26; c++)
      if (seen[c] && state[c] == 0 && !dfs(c))
        return "";

    // 4. Post-order is reversed topological order
    reverse(result.begin(), result.end());
    return result;
  }
};

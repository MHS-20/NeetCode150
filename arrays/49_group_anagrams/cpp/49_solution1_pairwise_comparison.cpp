#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
  vector<vector<string>> groupAnagrams(vector<string> &strs) {
    vector<vector<string>> result;

    for (string &s : strs) {
      bool placed = false;
      for (vector<string> &group : result) {
        if (isAnagram(s, group[0])) {
          group.push_back(s);
          placed = true;
          break;
        }
      }

      if (!placed) {
        result.push_back({s});
      }
    }
    return result;
  }

  bool isAnagram(string s, string t) {
    if (s.size() != t.size())
      return false;
    unordered_map<char, int> freq;
    for (char c : s)
      freq[c]++;
    for (char c : t) {
      if (--freq[c] < 0)
        return false;
    }
    return true;
  }
};

#include <array>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
  vector<vector<string>> groupAnagrams(vector<string> &strs) {
    string key;
    vector<vector<string>> result;
    unordered_map<string, vector<string>> groups;

    for (string s : strs) {
      key = serializeFrequency(s);
      groups[key].push_back(s);
    }

    for (auto &it : groups) {
      result.push_back(it.second);
    }

    return result;
  }

  string serializeFrequency(string s) {
    array<int, 26> alphabet = {};
    string key = "";

    for (char c : s)
      alphabet[c - 'a']++;

    for (int i = 0; i < 26; i++)
      key += to_string(alphabet[i]) + "#";
    return key;
  }
};

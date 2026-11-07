#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<string>> partition(string s) {
    vector<vector<string>> result;
    vector<string> path;
    backtrack(s, 0, path, result);
    return result;
  }

private:
  void backtrack(const string &s, int start, vector<string> &path,
                 vector<vector<string>> &result) {
    if (start == (int)s.size()) {
      result.push_back(path);
      return;
    }
    for (int i = start; i < (int)s.size(); i++) {
      if (!isPalindrome(s, start, i))
        continue;
      path.push_back(s.substr(start, i - start + 1));
      backtrack(s, i + 1, path, result);
      path.pop_back();
    }
  }

  bool isPalindrome(const string &s, int l, int r) {
    while (l < r)
      if (s[l++] != s[r--])
        return false;
    return true;
  }
};

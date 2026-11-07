#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  vector<string> letterCombinations(string digits) {
    vector<string> result;
    if (digits.empty())
      return result;
    string cur;
    backtrack(digits, 0, cur, result);
    return result;
  }

private:
  const vector<string> mapping = {"",    "",    "abc",  "def", "ghi",
                                  "jkl", "mno", "pqrs", "tuv", "wxyz"};

  void backtrack(const string &digits, int idx, string &cur,
                 vector<string> &result) {
    if (idx == (int)digits.size()) {
      result.push_back(cur);
      return;
    }
    for (char ch : mapping[digits[idx] - '0']) {
      cur.push_back(ch); // choose
      backtrack(digits, idx + 1, cur, result);
      cur.pop_back(); // un-choose
    }
  }
};

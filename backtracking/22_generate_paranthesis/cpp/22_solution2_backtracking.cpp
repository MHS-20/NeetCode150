#include <string>
#include <vector>
using namespace std;

class Solution {
public:
  vector<string> generateParenthesis(int n) {
    vector<string> res;
    string cur;
    cur.reserve(2 * n);
    backtrack(n, 0, 0, cur, res);
    return res;
  }

private:
  void backtrack(int n, int opened, int closed, string &cur,
                 vector<string> &res) {
    if (closed == n) {    // implies opened == n too
      res.push_back(cur); // copies once, only for finished answers
      return;
    }

    if (opened < n) {
      cur.push_back('(');                         // choose
      backtrack(n, opened + 1, closed, cur, res); // explore
      cur.pop_back();                             // undo
    }

    if (closed < opened) {
      cur.push_back(')');
      backtrack(n, opened, closed + 1, cur, res);
      cur.pop_back();
    }
  }
};

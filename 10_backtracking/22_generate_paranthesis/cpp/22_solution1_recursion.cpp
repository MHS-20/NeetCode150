#include <string>
#include <vector>
using namespace std;

class Solution {
public:
  vector<string> generateParenthesis(int n) {
    vector<string> res;
    build(n, 0, 0, "", res);
    return res;
  }

private:
  void build(int n, int opened, int closed, string cur, vector<string> &res) {
    if (closed == n) { // implies opened == n too
      res.push_back(cur);
      return;
    }
    if (opened < n)
      build(n, opened + 1, closed, cur + '(', res);
    if (closed < opened)
      build(n, opened, closed + 1, cur + ')', res);
  }
};

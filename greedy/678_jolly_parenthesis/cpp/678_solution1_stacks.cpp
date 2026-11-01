#include <stack>
#include <string>

using namespace std;

class Solution {
public:
  bool checkValidString(string s) {
    stack<int> open, star; // indices of unmatched '(' and '*'

    for (int i = 0; i < s.size(); i++) {
      switch (s[i]) {
      case '(':
        open.push(i);
        break;
      case '*':
        star.push(i);
        break;
      case ')':
        if (!open.empty())
          open.pop();
        else if (!star.empty())
          star.pop();
        else
          return false;
        break;
      }
    }

    // each leftover '(' needs a later '*' to close it
    while (!open.empty()) {
      if (star.empty() || star.top() < open.top())
        return false;
      open.pop();
      star.pop();
    }
    return true;
  }
};

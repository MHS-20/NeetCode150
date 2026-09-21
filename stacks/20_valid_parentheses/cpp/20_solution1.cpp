#include <stack>
#include <string>
using namespace std;

class Solution {
public:
  bool isValid(string s) {
    stack<char> expected; // closing brackets we still owe

    for (char c : s) {
      switch (c) {
      case '(':
        expected.push(')');
        break;
      case '[':
        expected.push(']');
        break;
      case '{':
        expected.push('}');
        break;
      default:
        if (expected.empty() || expected.top() != c)
          return false;
        expected.pop();
      }
    }
    return expected.empty();
  }
};

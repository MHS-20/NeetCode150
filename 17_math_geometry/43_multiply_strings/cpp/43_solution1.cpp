#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  string multiply(string num1, string num2) {
    int n = num1.size(), m = num2.size();
    vector<int> pos(n + m, 0);

    for (int i = n - 1; i >= 0; i--) {
      for (int j = m - 1; j >= 0; j--) {
        int mul = (num1[i] - '0') * (num2[j] - '0');
        int sum = mul + pos[i + j + 1];
        pos[i + j + 1] = sum % 10; // ones digit stays here
        pos[i + j] += sum / 10;    // carry goes one position left
      }
    }

    string res;
    for (int d : pos)
      if (!(res.empty() && d == 0)) // skip leading zeros
        res += char('0' + d);

    return res.empty() ? "0" : res;
  }
};

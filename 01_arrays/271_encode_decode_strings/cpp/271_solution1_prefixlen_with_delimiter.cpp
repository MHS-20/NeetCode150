#include <string>
#include <vector>
using namespace std;

class Solution {
public:
  char delimiter = '-';

  string encode(vector<string> &strs) {
    string encoded = "";
    for (const string &s : strs) {
      encoded += to_string(s.size()) + delimiter + s;
    }
    return encoded;
  }

  vector<string> decode(string s) {
    vector<string> res;
    int i = 0;

    while (i < s.size()) {
      int delimPos = s.find(delimiter, i);
      int len = stoi(s.substr(i, delimPos - i));

      string str = s.substr(delimPos + 1, len);
      res.push_back(str);

      i = delimPos + 1 + len;
    }

    return res;
  }
};

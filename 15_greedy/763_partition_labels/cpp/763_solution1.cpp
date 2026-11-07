#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> partitionLabels(string s) {
    int last[26];
    for (int i = 0; i < s.size(); i++)
      last[s[i] - 'a'] = i;

    vector<int> result;
    int start = 0, end = 0;

    for (int i = 0; i < s.size(); i++) {
      end = max(end, last[s[i] - 'a']);
      if (i == end) {
        result.push_back(end - start + 1);
        start = i + 1;
      }
    }

    return result;
  }
};

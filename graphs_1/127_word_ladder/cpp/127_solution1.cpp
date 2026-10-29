#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
    unordered_set<string> words(wordList.begin(), wordList.end());
    if (!words.count(endWord))
      return 0;

    queue<string> q;
    q.push(beginWord);
    words.erase(beginWord);
    int length = 1;

    while (!q.empty()) {
      int sz = q.size();
      for (int i = 0; i < sz; i++) {
        string w = q.front();
        q.pop();

        for (int pos = 0; pos < w.size(); pos++) {
          char original = w[pos];
          for (char c = 'a'; c <= 'z'; c++) {
            if (c == original)
              continue;
            w[pos] = c;
            if (w == endWord)
              return length + 1;
            if (words.count(w)) {
              words.erase(w);
              q.push(w);
            }
          }
          w[pos] = original;
        }
      }
      length++;
    }
    return 0;
  }
};

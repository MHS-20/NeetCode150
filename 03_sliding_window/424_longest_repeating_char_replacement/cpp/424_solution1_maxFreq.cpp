#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
  int characterReplacement(string s, int k) {
    unordered_map<char, int> reps; // reps of a char in current window
    int left = 0;
    int maxLen = k;
    int maxFreq = 0;

    for (int right = 0; right < s.size(); right++) {
      reps[s[right]]++;
      maxFreq = max(maxFreq, reps[s[right]]);

      if (right - left - maxFreq >= k) {
        reps[s[left]]--;
        left++;
      }

      maxLen = max(maxLen, right - left + 1);
    }

    return maxLen;
  }
};

// maxFreq never decreases, so the window can stay invalid for a while without
// changing the answer: every length it reaches has some valid window of that
// length. Full argument and trace in
// 00_docs/sliding_window/02_variable_size.md (Longest Repeating Character Replacement).

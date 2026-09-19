#include <array>
#include <string>
using namespace std;
class Solution {
public:
  bool checkInclusion(string s1, string s2) {
    if (s1.size() > s2.size())
      return false;

    array<int, 26> s1freq{}, windowfreq{};
    for (char c : s1)
      s1freq[c - 'a']++;
    for (int i = 0; i < s1.size(); i++)
      windowfreq[s2[i] - 'a']++;

    int match = 0;
    for (int i = 0; i < 26; i++)
      if (s1freq[i] == windowfreq[i])
        match++;
    if (match == 26)
      return true;

    int left = 0;
    for (int right = s1.size(); right < s2.size(); right++) {
      int r = s2[right] - 'a';
      int l = s2[left] - 'a';

      // add right char
      if (windowfreq[r] == s1freq[r])
        match--;
      windowfreq[r]++;
      if (windowfreq[r] == s1freq[r])
        match++;

      // remove left char
      if (windowfreq[l] == s1freq[l])
        match--;
      windowfreq[l]--;
      if (windowfreq[l] == s1freq[l])
        match++;

      left++;
      if (match == 26)
        return true;
    }
    return false;
  }
};

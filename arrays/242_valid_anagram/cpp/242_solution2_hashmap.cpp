#include <string>
#include <unordered_map>
using namespace std;

// the negative check plus the length check together
// guarantee the map is all zeros at the end

class Solution {
public:
  bool isAnagram(string s, string t) {
    if (s.size() != t.size())
      return false;
    unordered_map<char, int> map;

    for (char c : s)
      map[c]++;

    // default-constructs a new entry
    // when the key isn't found
    for (char c : t) {
      if (--map[c] < 0)
        return false;
    }
    return true;
  }
};

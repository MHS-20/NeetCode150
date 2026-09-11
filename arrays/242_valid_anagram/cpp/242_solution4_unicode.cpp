#include <codecvt>
#include <locale>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
  bool isAnagram(string s, string t) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    std::u32string s32 = converter.from_bytes(s);
    std::u32string t32 = converter.from_bytes(t);

    if (s32.size() != t32.size())
      return false;

    unordered_map<char32_t, int> map;
    for (char32_t c : s32)
      map[c]++;
    for (char32_t c : t32) {
      if (--map[c] < 0)
        return false;
    }
    return true;
  }
};

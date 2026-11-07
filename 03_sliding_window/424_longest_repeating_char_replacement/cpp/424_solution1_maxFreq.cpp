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

// ─────────────────────────────────────────────────────────────────────────
// WHY IT'S SAFE TO NEVER DECREASE maxFreq
// ─────────────────────────────────────────────────────────────────────────
//
// The key insight: the window's size never shrinks.
//
// Look at the loop: every iteration, `right` advances by 1 (window grows
// by 1 on the right). Then if the window is invalid, we shrink `left` by
// exactly 1 (window shrinks by 1 on the left). Net effect: the window
// size either stays the same or grows by 1 — it can never get smaller
// than it was on the previous iteration. So `right - left + 1` is
// monotonically non-decreasing throughout the whole scan.
//
// That means `maxLen` is really just tracking "how big has the window
// ever gotten" — and since the window size trend only goes up or
// flatlines, we don't need to actively search for a better
// smaller-but-still-valid window once we've found one of a certain size.
// We only care about ever reaching a bigger one.
//
// Now, why does a stale (too-high) maxFreq not cause us to miss a
// bigger valid window?
//
// Suppose maxFreq is currently overstating the real max count in the
// window (because the character that achieved it has since partially
// fallen out the left side). This makes our validity check more
// lenient than it should be — it might let an actually-invalid window
// slide through without shrinking.
//
// But here's the trick: if that happens, the window just keeps its
// current size (doesn't grow, since right-left+1 is capped by maxLen's
// current value being not exceeded)... actually more precisely: it
// doesn't matter, because that "invalid" window is never a new maximum
// unless the true frequency of some character in the current window
// genuinely reaches maxFreq again. If it can slide through as
// same-size, we just haven't found something bigger than before — no
// harm. To ever set a new maxLen, we need right - left + 1 to exceed
// the previous best, which requires the window to survive without
// shrinking, which requires maxFreq to have genuinely grown to match —
// and maxFreq only grows when a real character count in the window
// actually reaches that value. So a stale, too-high maxFreq can only
// make us retain an old-size window a bit longer than "fair," never
// fabricate a new, larger max.
//
// In short: we're not trying to track "is this window valid right now"
// perfectly — we're trying to track "has any window ever been bigger
// than my best so far," and for that purpose an optimistic
// (never-decreasing) maxFreq is sufficient and correct.
// ─────────────────────────────────────────────────────────────────────────

class Solution {
  lengthOfLongestSubstring(s) {
    const lastSeen = new Map();
    let maxLen = 0;
    let left = 0;

    for (let right = 0; right < s.length; right++) {
      const c = s[right];

      if (lastSeen.has(c) && lastSeen.get(c) >= left) {
        left = lastSeen.get(c) + 1;
      }

      lastSeen.set(c, right);
      maxLen = Math.max(maxLen, right - left + 1);
    }

    return maxLen;
  }
}

class Solution {
  characterReplacement(s, k) {
    const reps = new Map();
    let left = 0;
    let maxLen = k;
    let maxFreq = 0;

    for (let right = 0; right < s.length; right++) {
      const c = s[right];
      reps.set(c, (reps.get(c) || 0) + 1);
      maxFreq = Math.max(maxFreq, reps.get(c));

      if (right - left - maxFreq >= k) {
        const leftChar = s[left];
        reps.set(leftChar, reps.get(leftChar) - 1);
        left++;
      }

      maxLen = Math.max(maxLen, right - left + 1);
    }

    return maxLen;
  }
}

class Solution {
  minWindow(s, t) {
    const need = new Array(128).fill(0);
    for (let i = 0; i < t.length; i++) need[t.charCodeAt(i)]++;
    let missing = t.length;

    let bestStart = 0;
    let bestLen = Infinity;
    let left = 0;

    for (let right = 0; right < s.length; right++) {
      if (need[s.charCodeAt(right)]-- > 0) missing--; // this char was still needed

      while (missing === 0) { // window is valid: try to shrink
        if (right - left + 1 < bestLen) {
          bestStart = left;
          bestLen = right - left + 1;
        }
        if (++need[s.charCodeAt(left)] > 0) missing++; // we just removed a needed char
        left++;
      }
    }
    return bestLen === Infinity ? "" : s.substring(bestStart, bestStart + bestLen);
  }
}

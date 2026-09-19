class Solution {
  checkInclusion(s1, s2) {
    if (s1.length > s2.length) return false;

    const code = (str, i) => str.charCodeAt(i) - 97;
    const s1freq = new Array(26).fill(0);
    const windowfreq = new Array(26).fill(0);
    for (let i = 0; i < s1.length; i++) {
      s1freq[code(s1, i)]++;
      windowfreq[code(s2, i)]++;
    }

    let match = 0;
    for (let i = 0; i < 26; i++) if (s1freq[i] === windowfreq[i]) match++;
    if (match === 26) return true;

    let left = 0;
    for (let right = s1.length; right < s2.length; right++) {
      const r = code(s2, right);
      const l = code(s2, left);

      // add right char
      if (windowfreq[r] === s1freq[r]) match--;
      windowfreq[r]++;
      if (windowfreq[r] === s1freq[r]) match++;

      // remove left char
      if (windowfreq[l] === s1freq[l]) match--;
      windowfreq[l]--;
      if (windowfreq[l] === s1freq[l]) match++;

      left++;
      if (match === 26) return true;
    }
    return false;
  }
}

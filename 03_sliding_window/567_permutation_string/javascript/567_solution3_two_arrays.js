class Solution {
  checkInclusion(s1, s2) {
    const k = s1.length;
    const freq = new Array(26).fill(0);
    const wfreq = new Array(26).fill(0);
    for (let i = 0; i < k; i++) freq[s1.charCodeAt(i) - 97]++;

    // matches = number of the 26 letters whose window count equals freq
    let matches = 0;
    for (let i = 0; i < 26; i++)
      if (freq[i] === wfreq[i]) matches++; // empty window: letters absent from s1 already match

    // change the window count of s2[i] by delta, keeping `matches` in sync
    const update = (i, delta) => {
      const c = s2.charCodeAt(i) - 97;
      if (wfreq[c] === freq[c]) matches--; // was matching, about to change
      wfreq[c] += delta;
      if (wfreq[c] === freq[c]) matches++; // matches now
    };

    for (let right = 0; right < s2.length; right++) {
      update(right, +1); // char enters
      if (right >= k) update(right - k, -1); // char leaves
      if (matches === 26) return true;
    }
    return false;
  }
}

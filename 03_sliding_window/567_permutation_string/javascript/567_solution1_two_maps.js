class Solution {
  checkInclusion(s1, s2) {
    const k = s1.length;
    const freq = new Map();
    const wfreq = new Map();
    for (const c of s1) freq.set(c, (freq.get(c) ?? 0) + 1);

    const need = freq.size; // distinct letters in s1, fixed from here on
    let matches = 0; // letters of s1 whose window count equals freq

    // change the window count of c by delta, keeping `matches` in sync
    const update = (c, delta) => {
      if (!freq.has(c)) return; // not in s1: irrelevant
      const target = freq.get(c);
      const count = wfreq.get(c) ?? 0;
      if (count === target) matches--; // was matching, about to change
      wfreq.set(c, count + delta);
      if (count + delta === target) matches++; // matches now
    };

    for (let right = 0; right < s2.length; right++) {
      update(s2[right], +1); // char enters
      if (right >= k) update(s2[right - k], -1); // char leaves
      if (matches === need) return true;
    }
    return false;
  }
}

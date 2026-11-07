class Solution {
  checkInclusion(s1, s2) {
    const k = s1.length;
    const diff = new Map();
    let mismatched = 0;

    // shift a letter's diff by delta, keeping `mismatched` in sync
    const update = (c, delta) => {
      const d = diff.get(c) ?? 0;
      if (d === 0) mismatched++; // was balanced, about to break
      diff.set(c, d + delta);
      if (d + delta === 0) mismatched--; // now balanced again
    };

    for (const c of s1) update(c, -1);

    for (let right = 0; right < s2.length; right++) {
      update(s2[right], +1); // char enters
      if (right >= k) update(s2[right - k], -1); // char leaves
      if (mismatched === 0) return true;
    }
    return false;
  }
}

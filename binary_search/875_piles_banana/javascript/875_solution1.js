class Solution {
  minEatingSpeed(piles, h) {
    let maxPile = Math.max(...piles);
    let left = 1, right = maxPile;

    while (left < right) {
      const k = left + Math.floor((right - left) / 2);
      let hours = 0;
      for (const p of piles) hours += Math.ceil(p / k);

      if (hours > h) left = k + 1;
      else right = k;
    }
    return left;
  }
}

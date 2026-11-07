class Solution {
  maxProfit(prices) {
    let mn = Infinity;
    let profit = 0;

    for (const p of prices) {
      mn = Math.min(mn, p);
      profit = Math.max(profit, p - mn);
    }

    return profit;
  }
}

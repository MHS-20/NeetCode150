/**
 * @param {number} n
 * @param {number[][]} flights
 * @param {number} src
 * @param {number} dst
 * @param {number} k
 * @return {number}
 */
var findCheapestPrice = function (n, flights, src, dst, k) {
  let prices = new Array(n).fill(Infinity);
  prices[src] = 0;

  // Bellman-Ford limited to k + 1 rounds: round i allows i flights
  for (let round = 0; round <= k; round++) {
    const next = prices.slice(); // reads come from the previous round only
    for (const [from, to, price] of flights)
      if (prices[from] + price < next[to]) next[to] = prices[from] + price;
    prices = next;
  }

  return prices[dst] === Infinity ? -1 : prices[dst];
};

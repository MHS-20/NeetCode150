/**
 * @param {number} n
 * @param {number[][]} flights
 * @param {number} src
 * @param {number} dst
 * @param {number} k
 * @return {number}
 */
var findCheapestPrice = function (n, flights, src, dst, k) {
  const adj = Array.from({ length: n }, () => []); // from -> [to, price]
  for (const [f, t, p] of flights) adj[f].push([t, p]);

  const prices = new Array(n).fill(Infinity);
  let q = [[src, 0]]; // [city, cost so far]
  prices[src] = 0;

  // BFS by level, one level per flight (at most k + 1 levels)
  for (let flightsUsed = 0; flightsUsed <= k && q.length > 0; flightsUsed++) {
    // fresh array per level: Array.shift() is O(n)
    const next = [];
    for (const [c, p] of q) {
      for (const [to, price] of adj[c]) {
        if (p + price < prices[to]) {
          prices[to] = p + price;
          next.push([to, p + price]);
        }
      }
    }
    q = next;
  }

  return prices[dst] === Infinity ? -1 : prices[dst];
};

/**
 * @param {string[][]} tickets
 * @return {string[]}
 */
var findItinerary = function (tickets) {
  // destinations sorted descending, so pop() yields the smallest
  const adj = new Map();
  for (const [from, to] of tickets) {
    if (!adj.has(from)) adj.set(from, []);
    adj.get(from).push(to);
  }
  for (const dests of adj.values()) dests.sort().reverse();

  const result = [];
  const dfs = (cur) => {
    const dests = adj.get(cur) ?? [];
    while (dests.length) dfs(dests.pop()); // use this ticket
    result.push(cur); // post-order: no tickets left here
  };

  dfs("JFK");
  return result.reverse();
};

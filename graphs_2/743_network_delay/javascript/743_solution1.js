/**
 * @param {number[][]} times
 * @param {number} n
 * @param {number} k
 * @return {number}
 */
var networkDelayTime = function (times, n, k) {
  const adj = Array.from({ length: n + 1 }, () => []); // node -> [neighbor, weight]
  for (const [u, v, w] of times) adj[u].push([v, w]);

  const dist = new Array(n + 1).fill(Infinity);
  dist[k] = 0;

  // binary min-heap of [dist, node]: JS has no built-in priority queue
  const heap = [[0, k]];
  const push = (item) => {
    heap.push(item);
    let i = heap.length - 1;
    while (i > 0) {
      const p = (i - 1) >> 1;
      if (heap[p][0] <= heap[i][0]) break;
      [heap[p], heap[i]] = [heap[i], heap[p]];
      i = p;
    }
  };
  const pop = () => {
    const top = heap[0];
    const last = heap.pop();
    if (heap.length > 0) {
      heap[0] = last;
      let i = 0;
      for (;;) {
        let s = i;
        const l = 2 * i + 1;
        const r = l + 1;
        if (l < heap.length && heap[l][0] < heap[s][0]) s = l;
        if (r < heap.length && heap[r][0] < heap[s][0]) s = r;
        if (s === i) break;
        [heap[s], heap[i]] = [heap[i], heap[s]];
        i = s;
      }
    }
    return top;
  };

  while (heap.length > 0) {
    const [d, u] = pop();
    if (d > dist[u]) continue; // stale entry
    for (const [v, w] of adj[u]) {
      if (d + w < dist[v]) {
        dist[v] = d + w;
        push([dist[v], v]);
      }
    }
  }

  const ans = Math.max(...dist.slice(1));
  return ans === Infinity ? -1 : ans;
};

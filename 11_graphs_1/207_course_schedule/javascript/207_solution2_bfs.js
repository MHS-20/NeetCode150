/**
 * @param {number} numCourses
 * @param {number[][]} prerequisites
 * @return {boolean}
 */
var canFinish = function (numCourses, prerequisites) {
  const unlocks = Array.from({ length: numCourses }, () => []); // b -> courses that need b
  const remaining = new Array(numCourses).fill(0); // prerequisites still missing

  for (const [a, b] of prerequisites) {
    unlocks[b].push(a);
    remaining[a]++;
  }

  const queue = [];
  for (let c = 0; c < numCourses; c++) if (remaining[c] === 0) queue.push(c);

  let taken = 0;
  for (let head = 0; head < queue.length; head++) {
    taken++;
    for (const next of unlocks[queue[head]]) if (--remaining[next] === 0) queue.push(next);
  }

  return taken === numCourses;
};

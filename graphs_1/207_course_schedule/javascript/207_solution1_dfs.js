/**
 * @param {number} numCourses
 * @param {number[][]} prerequisites
 * @return {boolean}
 */
var canFinish = function (numCourses, prerequisites) {
  const adjacency = Array.from({ length: numCourses }, () => []);
  for (const [course, pre] of prerequisites) adjacency[course].push(pre);

  const state = new Array(numCourses).fill(0); // 0 = unvisited, 1 = on path, 2 = done

  const dfs = (node) => {
    if (state[node] === 1) return false; // back on the current path: cycle
    if (state[node] === 2) return true; // already fully explored

    state[node] = 1;
    for (const next of adjacency[node]) if (!dfs(next)) return false;
    state[node] = 2;
    return true;
  };

  for (let i = 0; i < numCourses; i++) if (!dfs(i)) return false;
  return true;
};

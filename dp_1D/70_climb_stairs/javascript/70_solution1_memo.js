/**
 * @param {number} n
 * @return {number}
 */
var climbStairs = function (n) {
  const memo = new Array(n + 1).fill(-1);

  const ways = (i) => {
    if (i <= 2) return i; // ways(1) = 1, ways(2) = 2
    if (memo[i] !== -1) return memo[i];
    return (memo[i] = ways(i - 1) + ways(i - 2));
  };

  return ways(n);
};

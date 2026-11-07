/**
 * @param {number} amount
 * @param {number[]} coins
 * @return {number}
 */
var change = function (amount, coins) {
  const dp = Array.from({ length: coins.length }, () => new Array(amount + 1).fill(-1));

  const f = (i, x) => {
    if (x === 0) return 1; // made the amount
    if (i === coins.length) return 0; // out of coins
    if (dp[i][x] !== -1) return dp[i][x];

    const skip = f(i + 1, x); // never use coin i again
    let take = 0;
    if (coins[i] <= x) take = f(i, x - coins[i]); // use coin i, stay at i (reuse allowed)

    return (dp[i][x] = skip + take);
  };

  return f(0, amount);
};

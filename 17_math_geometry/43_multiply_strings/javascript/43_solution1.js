/**
 * @param {string} num1
 * @param {string} num2
 * @return {string}
 */
var multiply = function (num1, num2) {
  const n = num1.length, m = num2.length;
  const pos = new Array(n + m).fill(0);

  for (let i = n - 1; i >= 0; i--) {
    for (let j = m - 1; j >= 0; j--) {
      const mul = (num1.charCodeAt(i) - 48) * (num2.charCodeAt(j) - 48);
      const sum = mul + pos[i + j + 1];
      pos[i + j + 1] = sum % 10; // ones digit stays here
      pos[i + j] += Math.floor(sum / 10); // carry goes one position left
    }
  }

  let res = "";
  for (const d of pos)
    if (!(res === "" && d === 0)) res += d; // skip leading zeros

  return res === "" ? "0" : res;
};

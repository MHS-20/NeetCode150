const MAPPING = ["", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"];

/**
 * @param {string} digits
 * @return {string[]}
 */
var letterCombinations = function (digits) {
  const result = [];
  if (digits.length === 0) return result;
  const cur = [];

  const backtrack = (idx) => {
    if (idx === digits.length) {
      result.push(cur.join(""));
      return;
    }
    for (const ch of MAPPING[digits[idx]]) {
      cur.push(ch); // choose
      backtrack(idx + 1);
      cur.pop(); // un-choose
    }
  };

  backtrack(0);
  return result;
};

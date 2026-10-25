const isPalindrome = (s, l, r) => {
  while (l < r) if (s[l++] !== s[r--]) return false;
  return true;
};

/**
 * @param {string} s
 * @return {string[][]}
 */
var partition = function (s) {
  const result = [];
  const path = [];

  const backtrack = (start) => {
    if (start === s.length) {
      result.push([...path]);
      return;
    }
    for (let i = start; i < s.length; i++) {
      if (!isPalindrome(s, start, i)) continue;
      path.push(s.slice(start, i + 1));
      backtrack(i + 1);
      path.pop();
    }
  };

  backtrack(0);
  return result;
};

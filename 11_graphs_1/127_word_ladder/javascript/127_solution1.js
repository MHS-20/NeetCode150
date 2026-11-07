/**
 * @param {string} beginWord
 * @param {string} endWord
 * @param {string[]} wordList
 * @return {number}
 */
var ladderLength = function (beginWord, endWord, wordList) {
  const words = new Set(wordList);
  if (!words.has(endWord)) return 0;

  let q = [beginWord];
  words.delete(beginWord);
  let length = 1;

  while (q.length > 0) {
    // swap in a fresh array per level: Array.shift() is O(n)
    const next = [];
    for (const word of q) {
      const w = word.split("");

      for (let pos = 0; pos < w.length; pos++) {
        const original = w[pos];
        for (let code = 97; code <= 122; code++) {
          const c = String.fromCharCode(code);
          if (c === original) continue;
          w[pos] = c;
          const s = w.join("");
          if (s === endWord) return length + 1;
          if (words.delete(s)) next.push(s);
        }
        w[pos] = original;
      }
    }
    q = next;
    length++;
  }
  return 0;
};

class Solution {
  isValid(s) {
    const expected = []; // closing brackets we still owe
    const closer = { "(": ")", "[": "]", "{": "}" };

    for (const c of s) {
      if (c in closer) expected.push(closer[c]);
      else if (expected.pop() !== c) return false;
    }
    return expected.length === 0;
  }
}

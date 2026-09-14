class Solution {
  encode(strs) {
    let encoded = "";
    for (const s of strs) {
      encoded += s.length + "-" + s;
    }
    return encoded;
  }

  decode(s) {
    const res = [];
    let i = 0;

    while (i < s.length) {
      const delimPos = s.indexOf("-", i);
      const len = parseInt(s.slice(i, delimPos), 10);

      res.push(s.slice(delimPos + 1, delimPos + 1 + len));
      i = delimPos + 1 + len;
    }

    return res;
  }
}

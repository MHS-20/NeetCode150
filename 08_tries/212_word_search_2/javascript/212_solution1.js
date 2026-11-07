class Node {
  constructor() {
    this.children = new Map();
    this.word = null; // non-null means a word ends here
  }
}

const DIRS = [
  [1, 0],
  [-1, 0],
  [0, 1],
  [0, -1],
];

function insert(root, word) {
  let cur = root;
  for (const ch of word) {
    if (!cur.children.has(ch)) cur.children.set(ch, new Node());
    cur = cur.children.get(ch);
  }
  cur.word = word;
}

function dfs(board, node, r, c, res) {
  const ch = board[r][c];
  const next = node.children.get(ch);
  if (!next) return;

  if (next.word !== null) {
    res.push(next.word);
    next.word = null; // avoid duplicates
  }

  board[r][c] = "#"; // mark visited
  for (const [dr, dc] of DIRS) {
    const nr = r + dr,
      nc = c + dc;
    if (nr < 0 || nr >= board.length || nc < 0 || nc >= board[0].length)
      continue;
    if (board[nr][nc] === "#") continue;
    dfs(board, next, nr, nc, res);
  }
  board[r][c] = ch; // unmark
}

/**
 * @param {character[][]} board
 * @param {string[]} words
 * @return {string[]}
 */
var findWords = function (board, words) {
  const root = new Node();
  for (const w of words) insert(root, w);

  const res = [];
  for (let r = 0; r < board.length; r++)
    for (let c = 0; c < board[0].length; c++) dfs(board, root, r, c, res);
  return res;
};

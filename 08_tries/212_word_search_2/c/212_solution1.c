#include <stdlib.h>

typedef struct Node {
  struct Node *children[26];
  char *word; // non-NULL means a word ends here
} Node;

static void insert(Node *root, char *word) {
  Node *cur = root;
  for (char *p = word; *p; p++) {
    int i = *p - 'a';
    if (!cur->children[i])
      cur->children[i] = calloc(1, sizeof(Node));
    cur = cur->children[i];
  }
  cur->word = word;
}

static void destroy(Node *n) {
  if (!n)
    return;
  for (int i = 0; i < 26; i++)
    destroy(n->children[i]);
  free(n);
}

static void dfs(char **board, int rows, int cols, Node *node, int r, int c,
                char **res, int *resSize) {
  static const int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  char ch = board[r][c];
  Node *next = node->children[ch - 'a'];
  if (!next)
    return;

  if (next->word) {
    res[(*resSize)++] = next->word;
    next->word = NULL; // avoid duplicates
  }

  board[r][c] = '#'; // mark visited
  for (int d = 0; d < 4; d++) {
    int nr = r + dirs[d][0], nc = c + dirs[d][1];
    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
      continue;
    if (board[nr][nc] == '#')
      continue;
    dfs(board, rows, cols, next, nr, nc, res, resSize);
  }
  board[r][c] = ch; // unmark
}

char **findWords(char **board, int boardSize, int *boardColSize, char **words,
                 int wordsSize, int *returnSize) {
  Node *root = calloc(1, sizeof(Node));
  for (int i = 0; i < wordsSize; i++)
    insert(root, words[i]);

  char **res = malloc(wordsSize * sizeof(char *));
  *returnSize = 0;
  for (int r = 0; r < boardSize; r++)
    for (int c = 0; c < boardColSize[0]; c++)
      dfs(board, boardSize, boardColSize[0], root, r, c, res, returnSize);

  destroy(root);
  return res;
}

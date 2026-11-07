#include <string>
#include <vector>

using namespace std;

class Solution {
  struct Node {
    Node *children[26] = {};
    string word; // non-empty means a word ends here
  };

  void insert(Node *root, const string &word) {
    Node *cur = root;
    for (char ch : word) {
      int i = ch - 'a';
      if (!cur->children[i])
        cur->children[i] = new Node();
      cur = cur->children[i];
    }
    cur->word = word;
  }

  void dfs(vector<vector<char>> &board, Node *node, int r, int c,
           vector<string> &res) {
    static constexpr int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    char ch = board[r][c];
    Node *next = node->children[ch - 'a'];
    if (!next)
      return;

    if (!next->word.empty()) {
      res.push_back(next->word);
      next->word.clear(); // avoid duplicates
    }

    board[r][c] = '#'; // mark visited
    int rows = board.size(), cols = board[0].size();
    for (auto &d : dirs) {
      int nr = r + d[0], nc = c + d[1];
      if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
        continue;
      if (board[nr][nc] == '#')
        continue;
      dfs(board, next, nr, nc, res);
    }
    board[r][c] = ch; // unmark
  }

public:
  vector<string> findWords(vector<vector<char>> &board, vector<string> &words) {
    Node *root = new Node();
    for (const string &w : words)
      insert(root, w);

    vector<string> res;
    for (int r = 0; r < (int)board.size(); r++)
      for (int c = 0; c < (int)board[0].size(); c++)
        dfs(board, root, r, c, res);
    return res;
  }
};

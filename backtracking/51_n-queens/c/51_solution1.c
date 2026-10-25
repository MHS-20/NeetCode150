#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int n;
  char **board;
  bool *cols, *diag1, *diag2;
  char ***rows;
  int size;
  int cap;
} State;

static void save(State *st) {
  if (st->size == st->cap) {
    st->cap = st->cap ? 2 * st->cap : 16;
    st->rows = realloc(st->rows, st->cap * sizeof(char **));
  }
  char **copy = malloc(st->n * sizeof(char *));
  for (int r = 0; r < st->n; r++)
    copy[r] = strdup(st->board[r]);
  st->rows[st->size++] = copy;
}

static void backtrack(State *st, int row) {
  int n = st->n;
  if (row == n) {
    save(st);
    return;
  }

  for (int col = 0; col < n; col++) {
    int d1 = row + col;         // "/" diagonal
    int d2 = row - col + n - 1; // "\" diagonal, shifted
    if (st->cols[col] || st->diag1[d1] || st->diag2[d2])
      continue;

    st->board[row][col] = 'Q';
    st->cols[col] = st->diag1[d1] = st->diag2[d2] = true;

    backtrack(st, row + 1);

    st->board[row][col] = '.';
    st->cols[col] = st->diag1[d1] = st->diag2[d2] = false;
  }
}

char ***solveNQueens(int n, int *returnSize, int **returnColumnSizes) {
  State st = {.n = n};
  st.board = malloc(n * sizeof(char *));
  for (int r = 0; r < n; r++) {
    st.board[r] = malloc(n + 1);
    memset(st.board[r], '.', n);
    st.board[r][n] = '\0';
  }
  st.cols = calloc(n, sizeof(bool));
  st.diag1 = calloc(2 * n - 1, sizeof(bool));
  st.diag2 = calloc(2 * n - 1, sizeof(bool));

  backtrack(&st, 0);

  for (int r = 0; r < n; r++)
    free(st.board[r]);
  free(st.board);
  free(st.cols);
  free(st.diag1);
  free(st.diag2);

  *returnSize = st.size;
  *returnColumnSizes = malloc((st.size ? st.size : 1) * sizeof(int));
  for (int i = 0; i < st.size; i++)
    (*returnColumnSizes)[i] = n;
  return st.rows;
}

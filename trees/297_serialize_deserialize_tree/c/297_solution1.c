#include "tree_node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constraint: at most 10^4 nodes, values in [-1000, 1000] -> at most "-1000#"
// per node plus "N#" for each of the (nodes + 1) null children
#define MAX_NODES 10000
#define MAX_LEN (MAX_NODES * 6 + (MAX_NODES + 1) * 2 + 1)

static void serDfs(struct TreeNode *root, char *ser, int *len) {
  if (!root) {
    *len += sprintf(ser + *len, "N#");
    return;
  }
  *len += sprintf(ser + *len, "%d#", root->val);
  serDfs(root->left, ser, len);
  serDfs(root->right, ser, len);
}

char *serialize(struct TreeNode *root) {
  char *ser = malloc(MAX_LEN);
  int len = 0;
  ser[0] = '\0';
  serDfs(root, ser, &len);
  return ser;
}

static struct TreeNode *desDfs(const char *data, int *pos) {
  const char *tok = data + *pos;
  *pos = strchr(tok, '#') - data + 1; // move cursor past '#'

  if (*tok == 'N')
    return NULL;

  struct TreeNode *root = malloc(sizeof(struct TreeNode));
  root->val = atoi(tok);           // atoi stops at '#'
  root->left = desDfs(data, pos);  // advances pos past the left subtree
  root->right = desDfs(data, pos); // continues from there
  return root;
}

struct TreeNode *deserialize(char *data) {
  int pos = 0;
  return desDfs(data, &pos);
}

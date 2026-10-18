#include <stdbool.h>
#include <stdlib.h>

typedef struct Trie {
  struct Trie *children[26];
  bool isEnd;
} Trie;

Trie *trieCreate() { return calloc(1, sizeof(Trie)); }

void trieInsert(Trie *obj, char *word) {
  Trie *cur = obj;
  for (; *word; word++) {
    int i = *word - 'a';
    if (!cur->children[i])
      cur->children[i] = trieCreate();
    cur = cur->children[i];
  }
  cur->isEnd = true;
}

// returns the node reached by following s, or NULL if the path breaks
static Trie *walk(Trie *cur, const char *s) {
  for (; *s && cur; s++)
    cur = cur->children[*s - 'a'];
  return cur;
}

bool trieSearch(Trie *obj, char *word) {
  Trie *node = walk(obj, word);
  return node && node->isEnd;
}

bool trieStartsWith(Trie *obj, char *prefix) { return walk(obj, prefix); }

void trieFree(Trie *obj) {
  if (!obj)
    return;
  for (int i = 0; i < 26; i++)
    trieFree(obj->children[i]);
  free(obj);
}

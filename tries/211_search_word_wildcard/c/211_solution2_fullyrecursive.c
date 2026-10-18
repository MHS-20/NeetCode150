#include <stdbool.h>
#include <stdlib.h>

typedef struct WordDictionary {
  struct WordDictionary *children[26];
  bool isEnd;
} WordDictionary;

WordDictionary *wordDictionaryCreate() {
  return calloc(1, sizeof(WordDictionary));
}

void wordDictionaryAddWord(WordDictionary *obj, char *word) {
  WordDictionary *cur = obj;
  for (; *word; word++) {
    int i = *word - 'a';
    if (!cur->children[i])
      cur->children[i] = wordDictionaryCreate();
    cur = cur->children[i];
  }
  cur->isEnd = true;
}

static bool dfs(const WordDictionary *cur, const char *word) {
  if (!cur)
    return false;
  if (!*word)
    return cur->isEnd;

  if (*word != '.')
    return dfs(cur->children[*word - 'a'], word + 1);

  for (int i = 0; i < 26; i++)
    if (dfs(cur->children[i], word + 1))
      return true;
  return false;
}

bool wordDictionarySearch(WordDictionary *obj, char *word) {
  return dfs(obj, word);
}

void wordDictionaryFree(WordDictionary *obj) {
  if (!obj)
    return;
  for (int i = 0; i < 26; i++)
    wordDictionaryFree(obj->children[i]);
  free(obj);
}

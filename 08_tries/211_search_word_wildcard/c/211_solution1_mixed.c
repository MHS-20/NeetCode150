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

static bool searchFrom(const WordDictionary *cur, const char *word) {
  for (; *word; word++) {
    if (*word != '.') {
      cur = cur->children[*word - 'a'];
      if (!cur)
        return false;
    } else {
      for (int i = 0; i < 26; i++) {
        if (cur->children[i] && searchFrom(cur->children[i], word + 1))
          return true;
      }
      return false;
    }
  }
  return cur->isEnd;
}

bool wordDictionarySearch(WordDictionary *obj, char *word) {
  return searchFrom(obj, word);
}

void wordDictionaryFree(WordDictionary *obj) {
  if (!obj)
    return;
  for (int i = 0; i < 26; i++)
    wordDictionaryFree(obj->children[i]);
  free(obj);
}

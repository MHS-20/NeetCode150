#include <stdlib.h>

#define MAX_KEY 10000 // 0 <= key <= 10^4, so an array can replace the hash map

typedef struct Node {
  int key, value;
  struct Node *prev, *next;
} Node;

typedef struct {
  int cap, size;
  Node *head, *tail; // dummy nodes
  Node *map[MAX_KEY + 1];
} LRUCache;

static Node *newNode(int key, int value) {
  Node *n = malloc(sizeof(Node));
  n->key = key;
  n->value = value;
  n->prev = n->next = NULL;
  return n;
}

static void removeNode(Node *n) {
  n->prev->next = n->next;
  n->next->prev = n->prev;
}

static void insertFront(LRUCache *obj, Node *n) {
  n->prev = obj->head;
  n->next = obj->head->next;
  obj->head->next->prev = n;
  obj->head->next = n;
}

LRUCache *lRUCacheCreate(int capacity) {
  LRUCache *obj = calloc(1, sizeof(LRUCache));
  obj->cap = capacity;
  obj->head = newNode(0, 0);
  obj->tail = newNode(0, 0);
  obj->head->next = obj->tail;
  obj->tail->prev = obj->head;
  return obj;
}

int lRUCacheGet(LRUCache *obj, int key) {
  Node *n = obj->map[key];
  if (!n)
    return -1;

  removeNode(n);
  insertFront(obj, n);
  return n->value;
}

void lRUCachePut(LRUCache *obj, int key, int value) {
  Node *n = obj->map[key];
  if (n) {
    n->value = value;
    removeNode(n);
    insertFront(obj, n);
    return;
  }

  if (obj->size == obj->cap) {
    Node *lru = obj->tail->prev;
    removeNode(lru);
    obj->map[lru->key] = NULL; // clear before free
    free(lru);
    obj->size--;
  }

  n = newNode(key, value);
  obj->map[key] = n;
  insertFront(obj, n);
  obj->size++;
}

void lRUCacheFree(LRUCache *obj) {
  Node *cur = obj->head;
  while (cur) {
    Node *nxt = cur->next;
    free(cur);
    cur = nxt;
  }
  free(obj);
}

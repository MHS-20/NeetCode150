#include <stdbool.h>
#include <stdlib.h>

#define MAX_USERS 501 // userId is in [1, 500]
#define FEED_SIZE 10

typedef struct {
  int time;
  int id;
} Tweet;

typedef struct {
  Tweet *list;
  int size;
  int cap;
} TweetList;

typedef struct {
  int timestamp;                        // global counter, ++ on every post
  TweetList tweets[MAX_USERS];          // userId -> tweets in post order
  bool following[MAX_USERS][MAX_USERS]; // follower -> followee
} Twitter;

typedef struct {
  int time;
  int id;
  int user;
  int idx;
} Entry;

static void swap(Entry *a, Entry *b) {
  Entry t = *a;
  *a = *b;
  *b = t;
}

static void siftUp(Entry *h, int i) {
  while (i > 0 && h[(i - 1) / 2].time < h[i].time) {
    swap(&h[(i - 1) / 2], &h[i]);
    i = (i - 1) / 2;
  }
}

static void siftDown(Entry *h, int n, int i) {
  for (;;) {
    int max = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && h[l].time > h[max].time)
      max = l;
    if (r < n && h[r].time > h[max].time)
      max = r;
    if (max == i)
      return;
    swap(&h[max], &h[i]);
    i = max;
  }
}

static void push(Entry *h, int *n, Entry e) {
  h[*n] = e;
  siftUp(h, (*n)++);
}

static Entry pop(Entry *h, int *n) {
  Entry top = h[0];
  h[0] = h[--*n];
  siftDown(h, *n, 0);
  return top;
}

Twitter *twitterCreate() { return calloc(1, sizeof(Twitter)); }

void twitterPostTweet(Twitter *obj, int userId, int tweetId) {
  TweetList *t = &obj->tweets[userId];
  if (t->size == t->cap) {
    t->cap = t->cap ? 2 * t->cap : 4;
    t->list = realloc(t->list, t->cap * sizeof(Tweet));
  }
  t->list[t->size++] = (Tweet){obj->timestamp++, tweetId};
}

int *twitterGetNewsFeed(Twitter *obj, int userId, int *retSize) {
  Entry pq[MAX_USERS]; // max-heap, at most one entry per user
  int n = 0;

  for (int user = 1; user < MAX_USERS; user++) {
    if (user != userId && !obj->following[userId][user])
      continue;
    const TweetList *t = &obj->tweets[user];
    if (t->size > 0) {
      int idx = t->size - 1;
      push(pq, &n, (Entry){t->list[idx].time, t->list[idx].id, user, idx});
    }
  }

  int *res = malloc(FEED_SIZE * sizeof(int));
  *retSize = 0;
  while (n > 0 && *retSize < FEED_SIZE) {
    Entry e = pop(pq, &n);
    res[(*retSize)++] = e.id;
    if (e.idx > 0) {
      Tweet next = obj->tweets[e.user].list[e.idx - 1];
      push(pq, &n, (Entry){next.time, next.id, e.user, e.idx - 1});
    }
  }

  return res;
}

void twitterFollow(Twitter *obj, int followerId, int followeeId) {
  obj->following[followerId][followeeId] = true;
}

void twitterUnfollow(Twitter *obj, int followerId, int followeeId) {
  obj->following[followerId][followeeId] = false;
}

void twitterFree(Twitter *obj) {
  for (int i = 0; i < MAX_USERS; i++)
    free(obj->tweets[i].list);
  free(obj);
}

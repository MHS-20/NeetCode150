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
  int timestamp;
  TweetList tweets[MAX_USERS];          // userId -> tweets in post order
  bool following[MAX_USERS][MAX_USERS]; // follower -> followee
} Twitter;

static void swap(Tweet *a, Tweet *b) {
  Tweet t = *a;
  *a = *b;
  *b = t;
}

static void siftUp(Tweet *h, int i) {
  while (i > 0 && h[(i - 1) / 2].time > h[i].time) {
    swap(&h[(i - 1) / 2], &h[i]);
    i = (i - 1) / 2;
  }
}

static void siftDown(Tweet *h, int n, int i) {
  for (;;) {
    int min = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && h[l].time < h[min].time)
      min = l;
    if (r < n && h[r].time < h[min].time)
      min = r;
    if (min == i)
      return;
    swap(&h[min], &h[i]);
    i = min;
  }
}

static Tweet pop(Tweet *h, int *n) {
  Tweet top = h[0];
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

// min-heap of size 10, ordered by timestamp: top is the oldest of the kept
// tweets
static void scan(const TweetList *t, Tweet *pq, int *n) {
  for (int i = 0; i < t->size; i++) {
    pq[*n] = t->list[i];
    siftUp(pq, (*n)++);
    if (*n > FEED_SIZE)
      pop(pq, n);
  }
}

int *twitterGetNewsFeed(Twitter *obj, int userId, int *retSize) {
  Tweet pq[FEED_SIZE + 1];
  int n = 0;

  scan(&obj->tweets[userId], pq, &n);
  for (int f = 1; f < MAX_USERS; f++) {
    if (f != userId && obj->following[userId][f])
      scan(&obj->tweets[f], pq, &n); // avoid scanning own tweets twice
  }

  // heap pops oldest first, so fill the result from the back
  int *res = malloc(FEED_SIZE * sizeof(int));
  *retSize = n;
  for (int i = n - 1; i >= 0; i--)
    res[i] = pop(pq, &n).id;
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

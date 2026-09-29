#include <stdlib.h>
#include <string.h>

typedef struct {
    int timestamp;
    char *value;
} Entry;

typedef struct {
    char *key;
    Entry *entries;
    int size;
    int capacity;
} Bucket;

typedef struct {
    Bucket *buckets;
    int size;
    int capacity;
} TimeMap;

TimeMap *timeMapCreate() {
    TimeMap *obj = malloc(sizeof(TimeMap));
    obj->size = 0;
    obj->capacity = 16;
    obj->buckets = malloc(sizeof(Bucket) * obj->capacity);
    return obj;
}

static Bucket *findOrCreateBucket(TimeMap *obj, char *key) {
    for (int i = 0; i < obj->size; i++) {
        if (strcmp(obj->buckets[i].key, key) == 0)
            return &obj->buckets[i];
    }

    if (obj->size == obj->capacity) {
        obj->capacity *= 2;
        obj->buckets = realloc(obj->buckets, sizeof(Bucket) * obj->capacity);
    }

    Bucket *b = &obj->buckets[obj->size++];
    b->key = strdup(key);
    b->size = 0;
    b->capacity = 4;
    b->entries = malloc(sizeof(Entry) * b->capacity);
    return b;
}

static Bucket *findBucket(TimeMap *obj, char *key) {
    for (int i = 0; i < obj->size; i++) {
        if (strcmp(obj->buckets[i].key, key) == 0)
            return &obj->buckets[i];
    }
    return NULL;
}

void timeMapSet(TimeMap *obj, char *key, char *value, int timestamp) {
    Bucket *b = findOrCreateBucket(obj, key);

    if (b->size == b->capacity) {
        b->capacity *= 2;
        b->entries = realloc(b->entries, sizeof(Entry) * b->capacity);
    }

    b->entries[b->size].timestamp = timestamp;
    b->entries[b->size].value = strdup(value);
    b->size++;
}

char *timeMapGet(TimeMap *obj, char *key, int timestamp) {
    Bucket *b = findBucket(obj, key);
    if (!b)
        return "";

    int left = 0, right = b->size - 1, resIdx = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (b->entries[mid].timestamp == timestamp)
            return b->entries[mid].value;
        if (b->entries[mid].timestamp > timestamp)
            right = mid - 1;
        else {
            resIdx = mid;
            left = mid + 1;
        }
    }

    return resIdx == -1 ? "" : b->entries[resIdx].value;
}

void timeMapFree(TimeMap *obj) {
    for (int i = 0; i < obj->size; i++) {
        free(obj->buckets[i].key);
        for (int j = 0; j < obj->buckets[i].size; j++)
            free(obj->buckets[i].entries[j].value);
        free(obj->buckets[i].entries);
    }
    free(obj->buckets);
    free(obj);
}

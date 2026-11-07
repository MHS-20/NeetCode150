#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  int *keys;
  int *values;
  bool *used;
  int capacity;
} HashMap;

static HashMap hashmap_create(int capacity) {
  HashMap map;
  map.capacity = capacity;
  map.keys = calloc(capacity, sizeof(int));
  map.values = calloc(capacity, sizeof(int));
  map.used = calloc(capacity, sizeof(bool));
  return map;
}

static void hashmap_free(HashMap *map) {
  free(map->keys);
  free(map->values);
  free(map->used);
}

static bool hashmap_get(HashMap *map, int key, int *value) {
  unsigned int idx = (unsigned int)key % map->capacity;

  while (map->used[idx]) {
    if (map->keys[idx] == key) {
      *value = map->values[idx];
      return true;
    }
    idx = (idx + 1) % map->capacity;
  }

  return false;
}

static void hashmap_put(HashMap *map, int key, int value) {
  unsigned int idx = (unsigned int)key % map->capacity;

  while (map->used[idx]) {
    idx = (idx + 1) % map->capacity;
  }

  map->used[idx] = true;
  map->keys[idx] = key;
  map->values[idx] = value;
}

int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
  HashMap seen = hashmap_create(numsSize * 2);
  int *result = NULL;
  *returnSize = 0;

  for (int i = 0; i < numsSize; i++) {
    int j;
    if (hashmap_get(&seen, nums[i], &j)) {
      result = (int *)malloc(2 * sizeof(int));
      result[0] = j;
      result[1] = i;
      *returnSize = 2;
      break;
    }
    hashmap_put(&seen, target - nums[i], i);
  }

  hashmap_free(&seen);
  return result;
}

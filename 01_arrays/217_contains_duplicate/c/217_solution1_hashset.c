#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int *slots;
    bool *used;
    int capacity;
} HashSet;

static HashSet hashset_create(int capacity) {
    HashSet set;
    set.capacity = capacity;
    set.slots = calloc(capacity, sizeof(int));
    set.used = calloc(capacity, sizeof(bool));
    return set;
}

static void hashset_free(HashSet *set) {
    free(set->slots);
    free(set->used);
}

static bool hashset_insert(HashSet *set, int value) {
    unsigned int idx = (unsigned int)value % set->capacity;

    while (set->used[idx]) {
        if (set->slots[idx] == value) {
            return false;
        }
        idx = (idx + 1) % set->capacity;
    }

    set->used[idx] = true;
    set->slots[idx] = value;
    return true;
}

bool containsDuplicate(int *nums, int numsSize) {
    if (numsSize == 0) {
        return false;
    }

    HashSet tracker = hashset_create(numsSize * 2);
    bool found = false;

    for (int i = 0; i < numsSize; i++) {
        if (!hashset_insert(&tracker, nums[i])) {
            found = true;
            break;
        }
    }

    hashset_free(&tracker);
    return found;
}

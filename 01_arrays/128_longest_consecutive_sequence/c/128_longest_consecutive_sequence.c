#include <stdlib.h>

static int cmp(const void *a, const void *b) {
    return *(const int *)a - *(const int *)b;
}

int longestConsecutive(int *nums, int numsSize) {
    if (numsSize == 0) {
        return 0;
    }

    qsort(nums, numsSize, sizeof(int), cmp);

    int longest = 1;
    int count = 1;

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] == nums[i - 1]) {
            continue;
        }

        if (nums[i] == nums[i - 1] + 1) {
            count++;
        } else {
            count = 1;
        }

        if (count > longest) {
            longest = count;
        }
    }

    return longest;
}

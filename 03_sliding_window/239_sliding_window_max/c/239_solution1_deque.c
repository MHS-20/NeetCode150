#include <stdlib.h>

int *maxSlidingWindow(int *nums, int numsSize, int k, int *returnSize) {
    int *maxs = malloc(sizeof(int) * (numsSize - k + 1));
    int *dq = malloc(sizeof(int) * numsSize); // indices, values decreasing
    int head = 0, tail = 0;
    *returnSize = 0;

    // i is the right pointer
    // i - k + 1 is the left pointer
    for (int i = 0; i < numsSize; i++) {
        if (head < tail && dq[head] < i - k + 1)
            head++;

        while (head < tail && nums[i] > nums[dq[tail - 1]])
            tail--;
        dq[tail++] = i;

        if (i >= k - 1)
            maxs[(*returnSize)++] = nums[dq[head]];
    }

    free(dq);
    return maxs;
}

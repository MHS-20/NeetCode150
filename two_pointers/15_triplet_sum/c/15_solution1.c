#include <stdlib.h>

static int cmp(const void *a, const void *b) {
    return *(const int *)a - *(const int *)b;
}

int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    qsort(nums, numsSize, sizeof(int), cmp);

    int capacity = 16;
    int **result = malloc(capacity * sizeof(int *));
    *returnColumnSizes = malloc(capacity * sizeof(int));
    *returnSize = 0;

    for (int idx = 0; idx < numsSize; idx++) {
        if (idx > 0 && nums[idx] == nums[idx - 1]) {
            continue;
        }

        int left = idx + 1, right = numsSize - 1;

        while (left < right) {
            int total = nums[idx] + nums[left] + nums[right];

            if (total == 0) {
                if (*returnSize == capacity) {
                    capacity *= 2;
                    result = realloc(result, capacity * sizeof(int *));
                    *returnColumnSizes = realloc(*returnColumnSizes, capacity * sizeof(int));
                }

                int *triplet = malloc(3 * sizeof(int));
                triplet[0] = nums[idx];
                triplet[1] = nums[left];
                triplet[2] = nums[right];
                result[*returnSize] = triplet;
                (*returnColumnSizes)[*returnSize] = 3;
                (*returnSize)++;

                left++;
                right--;
                while (left < right && nums[left] == nums[left - 1]) {
                    left++;
                }
                while (left < right && nums[right] == nums[right + 1]) {
                    right--;
                }
            } else if (total > 0) {
                right--;
            } else {
                left++;
            }
        }
    }

    return result;
}

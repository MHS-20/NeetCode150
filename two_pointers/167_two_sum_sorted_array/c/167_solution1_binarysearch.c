#include <stdlib.h>

int *twoSum(int *numbers, int numbersSize, int target, int *returnSize) {
    int *result = malloc(2 * sizeof(int));
    *returnSize = 2;

    for (int idx = 0; idx < numbersSize; idx++) {
        int diff = target - numbers[idx];
        int i = idx + 1, j = numbersSize - 1;

        while (i <= j) {
            int mid = i + (j - i) / 2;

            if (numbers[mid] == diff) {
                result[0] = idx + 1;
                result[1] = mid + 1;
                return result;
            }

            if (numbers[mid] > diff) {
                j = mid - 1;
            } else {
                i = mid + 1;
            }
        }
    }

    *returnSize = 0;
    return result;
}

#include <stdlib.h>

int *twoSum(int *numbers, int numbersSize, int target, int *returnSize) {
    int left = 0, right = numbersSize - 1;
    int *result = malloc(2 * sizeof(int));
    *returnSize = 2;

    while (left < right) {
        int total = numbers[left] + numbers[right];

        if (total == target) {
            result[0] = left + 1;
            result[1] = right + 1;
            return result;
        } else if (total < target) {
            left++;
        } else {
            right--;
        }
    }

    *returnSize = 0;
    return result;
}

class Solution {
    public int[] twoSum(int[] numbers, int target) {
        for (int idx = 0; idx < numbers.length; idx++) {
            int diff = target - numbers[idx];
            int i = idx + 1, j = numbers.length - 1;

            while (i <= j) {
                int mid = i + (j - i) / 2;

                if (numbers[mid] == diff) {
                    return new int[] {idx + 1, mid + 1};
                }

                if (numbers[mid] > diff) {
                    j = mid - 1;
                } else {
                    i = mid + 1;
                }
            }
        }

        return new int[] {};
    }
}

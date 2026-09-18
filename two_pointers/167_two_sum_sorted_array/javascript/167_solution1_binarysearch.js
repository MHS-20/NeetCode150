class Solution {
  twoSum(numbers, target) {
    for (let idx = 0; idx < numbers.length; idx++) {
      const diff = target - numbers[idx];
      let i = idx + 1;
      let j = numbers.length - 1;

      while (i <= j) {
        const mid = Math.floor((i + j) / 2);

        if (numbers[mid] === diff) return [idx + 1, mid + 1];

        if (numbers[mid] > diff) j = mid - 1;
        else i = mid + 1;
      }
    }

    return [];
  }
}

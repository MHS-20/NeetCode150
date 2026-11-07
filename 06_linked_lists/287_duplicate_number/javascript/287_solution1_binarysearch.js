var findDuplicate = function (nums) {
  let left = 1, right = nums.length - 1; // right = n

  while (left < right) {
    const mid = left + Math.floor((right - left) / 2);

    // count how many numbers are <= mid
    let count = 0;
    for (const x of nums) if (x <= mid) count++;

    if (count > mid) right = mid; // duplicate is in [left, mid]
    else left = mid + 1; // duplicate is in [mid + 1, right]
  }

  return left;
};

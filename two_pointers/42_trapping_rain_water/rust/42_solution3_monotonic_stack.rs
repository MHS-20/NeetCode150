struct Solution;

impl Solution {
    fn trap(height: Vec<i32>) -> i32 {
        let mut stack: Vec<usize> = Vec::new();
        let mut total = 0;

        for i in 0..height.len() {
            while let Some(&top) = stack.last() {
                if height[i] <= height[top] {
                    break;
                }

                let bottom = stack.pop().unwrap();

                match stack.last() {
                    None => break,
                    Some(&left) => {
                        let width = (i - left - 1) as i32;
                        let depth = height[left].min(height[i]) - height[bottom];
                        total += width * depth;
                    }
                }
            }

            stack.push(i);
        }

        total
    }
}

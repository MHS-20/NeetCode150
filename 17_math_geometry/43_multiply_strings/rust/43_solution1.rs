impl Solution {
    pub fn multiply(num1: String, num2: String) -> String {
        let (a, b) = (num1.as_bytes(), num2.as_bytes());
        let (n, m) = (a.len(), b.len());
        let mut pos = vec![0u32; n + m];

        for i in (0..n).rev() {
            for j in (0..m).rev() {
                let mul = (a[i] - b'0') as u32 * (b[j] - b'0') as u32;
                let sum = mul + pos[i + j + 1];
                pos[i + j + 1] = sum % 10; // ones digit stays here
                pos[i + j] += sum / 10; // carry goes one position left
            }
        }

        let res: String = pos
            .iter()
            .skip_while(|&&d| d == 0) // skip leading zeros
            .map(|&d| (b'0' + d as u8) as char)
            .collect();

        if res.is_empty() { "0".to_string() } else { res }
    }
}

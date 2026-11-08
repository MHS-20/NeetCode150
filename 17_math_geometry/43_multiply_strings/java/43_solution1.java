class Solution {
    public String multiply(String num1, String num2) {
        int n = num1.length(), m = num2.length();
        int[] pos = new int[n + m];

        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                int mul = (num1.charAt(i) - '0') * (num2.charAt(j) - '0');
                int sum = mul + pos[i + j + 1];
                pos[i + j + 1] = sum % 10; // ones digit stays here
                pos[i + j] += sum / 10;    // carry goes one position left
            }
        }

        StringBuilder res = new StringBuilder();
        for (int d : pos)
            if (!(res.length() == 0 && d == 0)) // skip leading zeros
                res.append(d);

        return res.length() == 0 ? "0" : res.toString();
    }
}

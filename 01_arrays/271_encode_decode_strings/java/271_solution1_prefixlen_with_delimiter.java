import java.util.ArrayList;
import java.util.List;

class Solution {
    public String encode(List<String> strs) {
        StringBuilder encoded = new StringBuilder();
        for (String s : strs) {
            encoded.append(s.length()).append('-').append(s);
        }
        return encoded.toString();
    }

    public List<String> decode(String s) {
        List<String> res = new ArrayList<>();
        int i = 0;

        while (i < s.length()) {
            int delimPos = s.indexOf('-', i);
            int len = Integer.parseInt(s.substring(i, delimPos));

            res.add(s.substring(delimPos + 1, delimPos + 1 + len));
            i = delimPos + 1 + len;
        }

        return res;
    }
}

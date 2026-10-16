import java.util.HashMap;
import java.util.Map;

class Solution {
    private Map<Integer, Integer> inIndex;
    private int preIdx;

    public TreeNode buildTree(int[] preorder, int[] inorder) {
        inIndex = new HashMap<>();
        for (int i = 0; i < inorder.length; i++)
            inIndex.put(inorder[i], i);

        preIdx = 0;
        return build(preorder, 0, inorder.length - 1);
    }

    private TreeNode build(int[] preorder, int inLo, int inHi) {
        if (inLo > inHi)
            return null;

        int rootVal = preorder[preIdx++];
        int mid = inIndex.get(rootVal);

        TreeNode cur = new TreeNode(rootVal);
        cur.left = build(preorder, inLo, mid - 1);
        cur.right = build(preorder, mid + 1, inHi);
        return cur;
    }
}

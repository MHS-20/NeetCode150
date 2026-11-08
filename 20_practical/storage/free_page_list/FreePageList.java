import java.util.Arrays;
import java.util.BitSet;
import java.util.Objects;

/**
 * Free-page manager for a paged file, in the style of a database file's freelist.
 *
 * Free pages form a singly linked list threaded through the pages themselves:
 * nextFree[p] is the page after p, as if stored in the free page's own bytes,
 * so the list costs no memory beyond the pages. Allocation pops the head and
 * freeing pushes onto it, both O(1). A bitmap of free pages catches double
 * frees, which would otherwise create a cycle in the list and hand the same
 * page to two owners.
 */
public class FreePageList {
    private static final int NONE = -1;

    private int[] nextFree;
    private final BitSet free = new BitSet();
    private int head = NONE;
    private int pageCount;
    private int freeCount;

    /** A file of pageCount pages, all free, allocated in order 0, 1, 2, ... */
    public FreePageList(int pageCount) {
        if (pageCount < 0) throw new IllegalArgumentException("negative page count");
        this.pageCount = pageCount;
        nextFree = new int[Math.max(pageCount, 8)];
        for (int p = pageCount - 1; p >= 0; p--) push(p);
    }

    /** Returns a free page; grows the file by one page when none is free. */
    public int allocate() {
        if (head == NONE) {
            int p = pageCount++;
            if (p == nextFree.length) nextFree = Arrays.copyOf(nextFree, 2 * p);
            return p;
        }
        int p = head;
        head = nextFree[p];
        free.clear(p);
        freeCount--;
        return p;
    }

    public void free(int page) {
        if (page < 0 || page >= pageCount) throw new IllegalArgumentException("page out of range: " + page);
        if (free.get(page)) throw new IllegalStateException("double free: " + page);
        push(page);
    }

    public int pageCount() {
        return pageCount;
    }

    public int freeCount() {
        return freeCount;
    }

    private void push(int p) {
        nextFree[p] = head;
        head = p;
        free.set(p);
        freeCount++;
    }

    // ---- checks -------------------------------------------------------------

    public static void main(String[] args) {
        stage1();
        stage2();
        stage3();
        stage4();
        System.out.println("all checks passed");
    }

    static void stage1() {
        FreePageList f = new FreePageList(3);
        eq(f.allocate(), 0, "first page");
        eq(f.allocate(), 1, "second page");
        f.free(0);
        eq(f.allocate(), 0, "freed page reused first");
        f.free(1);
        f.free(0);
        eq(f.allocate(), 0, "last freed, first reused");
        eq(f.allocate(), 1, "then the one before");
        eq(f.allocate(), 2, "then the untouched page");
    }

    static void stage2() {
        FreePageList f = new FreePageList(2);
        int p = f.allocate();
        f.free(p);
        throwsEx(IllegalStateException.class, () -> f.free(p), "double free");
        throwsEx(IllegalStateException.class, () -> f.free(1), "freeing a never-allocated page");
        throwsEx(IllegalArgumentException.class, () -> f.free(2), "page past the end");
        throwsEx(IllegalArgumentException.class, () -> f.free(-1), "negative page");
        eq(f.allocate(), 0, "list intact after rejected frees");
        eq(f.allocate(), 1, "list intact after rejected frees");
    }

    static void stage3() {
        FreePageList f = new FreePageList(1);
        eq(f.allocate(), 0, "existing page");
        eq(f.allocate(), 1, "file grows");
        eq(f.pageCount(), 2, "page count after growth");
        for (int i = 2; i < 100; i++) eq(f.allocate(), i, "growth beyond the array");
        f.free(50);
        eq(f.allocate(), 50, "freed page preferred over growth");
        eq(f.allocate(), 100, "growth continues");
    }

    static void stage4() {
        FreePageList f = new FreePageList(4);
        eq(f.freeCount(), 4, "all free");
        f.allocate();
        f.allocate();
        eq(f.freeCount(), 2, "after two allocations");
        f.free(0);
        eq(f.freeCount(), 3, "after a free");
        for (int i = 0; i < 3; i++) f.allocate();
        eq(f.freeCount(), 0, "none free");
        f.allocate(); // growth does not touch the count
        eq(f.freeCount(), 0, "still none free after growth");
    }

    static void eq(Object got, Object expected, String what) {
        if (!Objects.equals(got, expected))
            throw new AssertionError(what + ": expected " + expected + ", got " + got);
    }

    static void throwsEx(Class<? extends Exception> type, Runnable r, String what) {
        try {
            r.run();
        } catch (Exception e) {
            if (type.isInstance(e)) return;
            throw new AssertionError(what + ": expected " + type.getSimpleName() + ", got " + e);
        }
        throw new AssertionError(what + ": expected " + type.getSimpleName());
    }
}

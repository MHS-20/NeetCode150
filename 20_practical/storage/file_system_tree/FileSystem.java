import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.TreeMap;

/**
 * In-memory file system: a tree of directories and files, addressed by
 * absolute paths such as "/a/b/file.txt".
 *
 * Directories keep their children in a TreeMap so listings come out sorted.
 * Directory and file are separate types, so a path that tries to descend
 * through a file, or read a directory as a file, is caught by a type check.
 */
public class FileSystem {

    private sealed interface Entry permits Dir, File {}

    private static final class Dir implements Entry {
        final Map<String, Entry> children = new TreeMap<>();
    }

    private static final class File implements Entry {
        final StringBuilder content = new StringBuilder();
    }

    public static class FsException extends RuntimeException {
        FsException(String message) {
            super(message);
        }
    }

    private final Dir root = new Dir();

    /** Creates the directory and any missing parents; existing directories are fine. */
    public void mkdir(String path) {
        Dir d = root;
        for (String name : split(path)) d = childDir(d, name, path, true);
    }

    /** Sorted names in a directory, or the file's own name for a file. */
    public List<String> ls(String path) {
        List<String> parts = split(path);
        Entry e = resolve(parts, path);
        if (e instanceof Dir d) return new ArrayList<>(d.children.keySet());
        return List.of(parts.get(parts.size() - 1));
    }

    /** Appends to a file, creating it and any missing parent directories. */
    public void append(String path, String text) {
        List<String> parts = split(path);
        if (parts.isEmpty()) throw new FsException("not a file: " + path);
        Dir d = root;
        for (String name : parts.subList(0, parts.size() - 1)) d = childDir(d, name, path, true);
        Entry e = d.children.computeIfAbsent(parts.get(parts.size() - 1), n -> new File());
        if (!(e instanceof File f)) throw new FsException("is a directory: " + path);
        f.content.append(text);
    }

    public String read(String path) {
        if (!(resolve(split(path), path) instanceof File f)) throw new FsException("is a directory: " + path);
        return f.content.toString();
    }

    /** Removes a file, or a directory with everything under it. */
    public void rm(String path) {
        List<String> parts = split(path);
        if (parts.isEmpty()) throw new FsException("cannot remove /");
        Dir parent = root;
        for (String name : parts.subList(0, parts.size() - 1)) parent = childDir(parent, name, path, false);
        if (parent.children.remove(parts.get(parts.size() - 1)) == null) throw new FsException("no such path: " + path);
    }

    /** Total length of the file contents at or under path. */
    public long size(String path) {
        return size(resolve(split(path), path));
    }

    private static long size(Entry e) {
        return switch (e) {
            case File f -> f.content.length();
            case Dir d -> d.children.values().stream().mapToLong(FileSystem::size).sum();
        };
    }

    private Entry resolve(List<String> parts, String path) {
        Entry e = root;
        for (String name : parts) {
            if (!(e instanceof Dir d)) throw new FsException("not a directory: " + path);
            e = d.children.get(name);
            if (e == null) throw new FsException("no such path: " + path);
        }
        return e;
    }

    private static Dir childDir(Dir d, String name, String path, boolean create) {
        Entry e = create ? d.children.computeIfAbsent(name, n -> new Dir()) : d.children.get(name);
        if (e == null) throw new FsException("no such path: " + path);
        if (!(e instanceof Dir child)) throw new FsException("not a directory: " + path);
        return child;
    }

    /** "/a//b/" -> [a, b]; "/" -> []. Paths must be absolute. */
    private static List<String> split(String path) {
        if (path == null || !path.startsWith("/")) throw new FsException("path must be absolute: " + path);
        List<String> parts = new ArrayList<>();
        for (String s : path.split("/")) {
            if (s.isEmpty()) continue;
            if (s.equals(".") || s.equals("..")) throw new FsException("unsupported path segment: " + path);
            parts.add(s);
        }
        return parts;
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
        FileSystem fs = new FileSystem();
        eq(fs.ls("/"), List.of(), "empty root");
        fs.mkdir("/b/c");
        fs.mkdir("/a");
        fs.mkdir("/b/c"); // already exists: no error
        eq(fs.ls("/"), List.of("a", "b"), "sorted listing");
        eq(fs.ls("/b"), List.of("c"), "nested directory");
        eq(fs.ls("//b///"), List.of("c"), "repeated and trailing slashes");
    }

    static void stage2() {
        FileSystem fs = new FileSystem();
        fs.append("/x/y/notes.txt", "hello");
        fs.append("/x/y/notes.txt", " world");
        eq(fs.read("/x/y/notes.txt"), "hello world", "appended content");
        eq(fs.ls("/x/y"), List.of("notes.txt"), "file listed in its directory");
        eq(fs.ls("/x/y/notes.txt"), List.of("notes.txt"), "ls on a file");
    }

    static void stage3() {
        FileSystem fs = new FileSystem();
        fs.append("/f", "data");
        fs.mkdir("/d");
        throwsFs(() -> fs.mkdir("/f/sub"), "mkdir through a file");
        throwsFs(() -> fs.append("/f/g", "x"), "file under a file");
        throwsFs(() -> fs.append("/d", "x"), "append to a directory");
        throwsFs(() -> fs.read("/d"), "read a directory");
        throwsFs(() -> fs.read("/missing"), "read a missing file");
        throwsFs(() -> fs.ls("/f/x"), "ls through a file");
        throwsFs(() -> fs.ls("relative/path"), "relative path");
        eq(fs.read("/f"), "data", "file untouched by failed operations");
    }

    static void stage4() {
        FileSystem fs = new FileSystem();
        fs.append("/a/one", "123");
        fs.append("/a/b/two", "45");
        fs.append("/c", "6789");
        eq(fs.size("/"), 9L, "whole tree");
        eq(fs.size("/a"), 5L, "subtree");
        eq(fs.size("/c"), 4L, "single file");
        fs.rm("/a/b");
        eq(fs.size("/"), 7L, "after removing a directory");
        eq(fs.ls("/a"), List.of("one"), "directory listing after rm");
        throwsFs(() -> fs.rm("/a/b"), "removing a missing path");
        throwsFs(() -> fs.rm("/"), "removing the root");
    }

    static void eq(Object got, Object expected, String what) {
        if (!Objects.equals(got, expected))
            throw new AssertionError(what + ": expected " + expected + ", got " + got);
    }

    static void throwsFs(Runnable r, String what) {
        try {
            r.run();
        } catch (FsException e) {
            return;
        }
        throw new AssertionError(what + ": expected FsException");
    }
}

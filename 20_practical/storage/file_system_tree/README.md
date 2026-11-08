# In-Memory File System

A tree of directories and files addressed by absolute paths like `/a/b/notes.txt`. Similar to LeetCode 588, Design In-Memory File System, with error handling and removal added.

## Stages

1. **Directories.** `mkdir(path)` creates a directory and any missing parents; an existing directory is not an error. `ls(path)` lists a directory's entries in sorted order. Repeated and trailing slashes are ignored.
2. **Files.** `append(path, text)` appends to a file, creating it and its parent directories if needed. `read(path)` returns its content. `ls` on a file returns just the file's name.
3. **Errors.** Reject, with an error and without changing the existing file or directory: going through a file as if it were a directory, appending to or reading a directory, reading a missing path, relative paths.
4. **Removal and size.** `rm(path)` removes a file, or a directory with everything under it; removing `/` is an error. `size(path)` returns the total length of the file contents at or under `path`.

## Design notes

Directories and files are two different types implementing one sealed interface, so "is this a directory?" is a type check instead of a boolean flag. With a flag, a file node still has a `children` map, and nothing stops code from putting entries in it. Children are kept in a `TreeMap`, so `ls` is sorted without sorting on every call.

As with `mkdir -p`, a `mkdir` that fails partway keeps the directories it already created.

## Changes from the original version

The original used one node type with an `isFile` flag. `addFile` assumed the path started with `/` by skipping the first segment, could set content on an existing directory, and `mkdir` could descend into a file. Errors were plain `RuntimeException`s.

## Files

`FileSystem.java`: the solution, with checks for each stage in `main`. Run with `java FileSystem.java` (Java 21+).

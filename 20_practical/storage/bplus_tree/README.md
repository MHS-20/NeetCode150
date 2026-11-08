# B+ Tree

An ordered map from keys to values, stored as a B+ tree, the structure behind most database indexes.

## Stages

1. **Lookup in a leaf.** With fewer keys than the node limit, the tree is a single leaf holding sorted keys and their values. `put(key, value)` and `get(key)`.
2. **Splits.** A node holds at most `maxKeys` keys. Inserting into a full node splits it, and the tree must stay balanced: every leaf at the same depth. Lookups stay O(log n).
3. **Range scans.** `range(from, to)` returns the entries with `from <= key < to` in key order, without visiting any leaf twice.
4. **Updates.** `put` on an existing key replaces its value and does not change the tree's shape.

## Design notes

Values are stored only in the leaves, and each leaf links to the next one. A range scan finds the first leaf with one descent and then follows the links. A plain B-tree stores values in internal nodes too, so its range scan has to move up and down the tree.

Internal nodes hold separators: child `i` contains the keys `k` with `keys[i-1] <= k < keys[i]`. The two kinds of split differ:

- a **leaf** split copies the first key of the new right leaf up into the parent, and the key stays in the leaf, because the leaves must hold every key;
- an **internal** split moves its middle key up, and the key leaves that level.

When the root splits, a new root is created above it. The tree only grows at the top, which keeps all leaves at one depth.

`main` checks the tree against a `TreeMap` on 5000 shuffled keys, and verifies the invariants: node sizes, separators bounding their subtrees, one leaf depth, and a sorted leaf chain holding every key. Deletion, which needs borrowing from and merging with neighbours, is left out.

## Changes from the original version

The original was titled B+ tree but implemented a B-tree: keys sat in internal nodes and the leaves were not linked, so there was no efficient range scan. It also stored only keys, no values.

## Files

`BPlusTree.java`: the solution, with checks for each stage in `main`. Run with `java BPlusTree.java` (Java 21+).

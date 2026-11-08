# P, NP, NP-hard and NP-complete

## The four definitions

**P (Polynomial time)** — *easy to solve.* The class of problems that can be **solved efficiently**: an algorithm exists that finds the solution in polynomial time, O(n), O(n²), O(n³) and so on.

**NP (Nondeterministic Polynomial time)** — *easy to verify* (but maybe not easy to solve). The class of problems where, **if someone hands you a solution**, you can **check** that it is correct in polynomial time — even when finding it might be hard.

**NP-hard.** A problem is NP-hard if every problem in NP can be reduced to it in polynomial time; that is, if you could solve this one efficiently, you could solve everything in NP efficiently. NP-hard problems are at least as hard as the hardest problems in NP, but **they need not be in NP themselves** — some are not even verifiable, and some are undecidable. Others are solvable but only inefficiently.

**NP-complete.** A problem is NP-complete when it is **both**:

1. in NP — solutions can be verified in polynomial time, **and**
2. NP-hard — as hard as any other problem in NP.

These are the hardest problems *inside* NP. Solve one of them efficiently and every NP problem falls with it. They are **decidable**: a solution either exists or it does not, and you can always find the answer by trying every possibility — brute force, exhaustive search — but that search takes an astronomically long time as the input grows.

```
        ┌─────────────────────────────┐
        │            NP-hard          │
        │   ┌──────────────┐          │   ← halting problem lives here,
        │   │ NP-complete  │          │     outside NP: not even verifiable
   ┌────┼───┤ SAT, TSP-dec │          │
   │ NP │   │ 3-SAT, ...   │          │
   │    │   └──────────────┘          │
   │ ┌──┴─┐                           │
   │ │ P  │  sorting, shortest path   │
   │ └────┘                           │
   └────────┴──────────────────────────┘

        (drawn assuming P ≠ NP)
```

## Why "polynomial" is the dividing line

The split looks arbitrary — is O(n¹⁰⁰) really "efficient"? — and there are two good reasons for it.

**Polynomials compose; exponentials explode.** A polynomial algorithm calling another polynomial algorithm is still polynomial. That closure makes P a stable class that does not depend on the machine model, the language, or the constant factors.

**The practical gap is enormous and does not close with better hardware.** Doubling your computer's speed lets an O(n) algorithm handle twice the input, and lets an O(2ⁿ) algorithm handle *one more element*. That is the real distinction, and it is why the theoretical line matches the practical one closely enough to be useful.

```
n = 50:    n²  = 2,500              2ⁿ ≈ 10¹⁵   (weeks)
n = 100:   n²  = 10,000             2ⁿ ≈ 10³⁰   (longer than the universe has existed)
```

## Verification vs. solution — the whole idea

NP is defined by a **certificate**: a proposed answer that can be checked quickly.

Sudoku is the clearest example. Filling in a blank grid is hard and may take a long search. Checking a *filled* grid is trivial — scan every row, column and box once. Finding is hard, checking is easy.

For **Subset Sum** — is there a subset of these integers adding up to exactly T? — the certificate is the subset itself. Add its elements and compare to T: linear. Finding that subset among 2ⁿ candidates is the hard part.

Every problem in P is also in NP, because if you can *solve* something quickly you can verify a proposed answer quickly by just solving it yourself and comparing. So P ⊆ NP. Whether the containment is strict is the open question below.

## Reductions: why one problem's hardness transfers

A **polynomial-time reduction** from problem A to problem B is a fast translation turning any instance of A into an instance of B, such that B's answer gives you A's.

```
instance of A  ──translate (polynomial)──>  instance of B
                                                  │
                                            solve B
                                                  │
answer to A    <────────────────────────────  answer
```

If such a translation exists and B is easy, then A is easy: translate, solve, done. Read the other way, if A is known to be hard, then B must be hard too — otherwise A's hardness would evaporate.

That contrapositive is how NP-completeness spreads. Cook and Levin proved SAT is NP-complete directly, from the definition of a nondeterministic machine. Every NP-completeness proof since then works by reducing a *known* NP-complete problem to the new one, which is why the list below is so long and so varied: they are all the same problem wearing different clothes.

**In practice this is what "prove it's NP-hard" means**: show that some classic NP-complete problem is a special case of yours, or translates into yours.

## Decision vs. optimization

The classes are defined over **decision problems** — questions with a yes/no answer. That is a technical requirement, since "verify a certificate" needs something definite to verify.

Most real problems are **optimization** problems, and each has a decision twin:

| Optimization (NP-hard) | Decision (NP-complete) |
|---|---|
| find the shortest tour | is there a tour of length ≤ X? |
| maximise knapsack value | is there a packing with value ≥ V and weight ≤ W? |
| find the smallest vertex cover | is there a cover of size ≤ k? |

The optimization version is **NP-hard but not in NP**, which is the usual reason a problem gets called NP-hard rather than NP-complete. The subtlety is verification: given a claimed shortest tour, you can check its length quickly, but you cannot quickly check that *nothing shorter exists* — that would require examining every other tour.

The two versions are equally hard up to a polynomial factor, since you can binary-search on X and call the decision version each time.

## The open question

> **Can every problem that is easy to verify also be solved easily?** Is P = NP?

- If **P = NP**, every NP-complete problem has an efficient algorithm, and finding a solution is never fundamentally harder than checking one.
- If **P ≠ NP** — which most researchers believe — **no polynomial-time algorithm exists** for NP-complete problems, and the exponential search is unavoidable.

It has never been proven either way. It is one of the biggest open problems in computer science, and one of the Clay Institute's million-dollar Millennium Prize problems.

Two things worth noting about what the answer would mean. Decades of failed attempts on thousands of NP-complete problems is evidence, not proof. And a proof of P = NP would not automatically make anything fast in practice — an O(n¹⁰⁰) algorithm settles the theory and changes nothing about how you would actually solve the problem.

## NP-complete vs. NP-hard, side by side

**NP-complete** — the hardest problems *still inside* NP.

- You can **verify** a proposed solution quickly.
- You cannot **find** it efficiently, as far as anyone knows.
- Decidable: brute force always terminates with the right answer, eventually.
- Example: SAT. Hand someone a truth assignment and they can check it fast.

**NP-hard** — the hardest problems *overall*, possibly harder than anything in NP.

- You **might not be able to verify** a solution efficiently.
- The class includes problems outside NP entirely: optimization versions, and undecidable problems.
- Example: the **halting problem** — does this program terminate? — is NP-hard and not in NP. No algorithm decides it at all, at any speed, so there is nothing to verify.

The relationship in one line: **NP-complete = NP ∩ NP-hard.**

## What to do when a problem is NP-hard

Recognising NP-hardness is not a dead end; it tells you to stop looking for an exact polynomial algorithm and choose a compromise instead. Five standard escapes:

**Exponential but smart.** Brute force with heavy pruning ([`8a_backtracking_basics.md`](../08_techniques/8a_backtracking_basics.md)) or bitmask DP. TSP by dynamic programming is O(2ⁿ · n²) rather than O(n!) — still exponential, but 20 cities become feasible where 20! would not.

**Pseudo-polynomial DP.** Knapsack is NP-complete, yet the standard DP runs in O(n·W) ([`10b_dp_1d_vs_2d.md`](../10_dynamic_programming/10b_dp_1d_vs_2d.md)). There is no contradiction: W is a *value*, and writing it takes only log W bits, so O(n·W) is exponential in the input's actual size. It is fast whenever W happens to be small, and hopeless when W is 10¹⁸.

**Approximation with a guarantee.** Accept an answer provably within a factor of optimal. Greedy vertex cover is within 2×; bin packing has simple algorithms within 11/9 of optimal.

**Heuristics with no guarantee.** Simulated annealing, genetic algorithms, industrial SAT solvers. Modern SAT solvers routinely handle instances with millions of variables despite the worst case being exponential — worst-case hardness says nothing about typical inputs.

**Restrict the input.** Many NP-complete problems become polynomial on special structures. Graph colouring is hard in general but easy on trees and on bipartite graphs; 2-SAT is in P while 3-SAT is NP-complete.

## Where this touches the interview problems

Several problems in this set are NP-complete in general, and are tractable only because the constraints are small:

- **Subset Sum / Partition Equal Subset Sum** — NP-complete; solved by pseudo-polynomial DP because the target sum is bounded.
- **0/1 Knapsack** — same.
- **Travelling Salesman / Hamiltonian path** — bitmask DP, hence the `n ≤ 20` constraint ([masking](../11_bit_manipulation/11d_masking.md#bitmask-dp)).
- **N-Queens, Sudoku solver, Word Search II** — exhaustive search with pruning.
- **Graph colouring**, when it appears, is usually restricted to 2 colours, which is bipartiteness checking and is in P.

The practical lesson connects straight to [`1b_pattern_recognition.md`](1b_pattern_recognition.md): **when a problem's constraints are tiny (n ≤ 20), that is often a signal the problem is NP-hard** and the setter knows exponential search is the intended answer. You are not missing a clever polynomial trick, because none is known to exist.

---

# Reference: the classic problems

Separated from the explanation above; this is a lookup list.

### 1. Boolean Satisfiability (SAT) — NP-complete

Given a Boolean formula using AND, OR and NOT, is there an assignment of True/False to the variables that makes the formula true? The first problem proven NP-complete (Cook–Levin), and the root of nearly every other proof.

### 2. 3-SAT — NP-complete

SAT restricted so that every clause has exactly three literals, for example `(A ∨ ¬B ∨ C)`. Still NP-complete, and the usual starting point for reductions because its rigid shape is easier to work with. **2-SAT, by contrast, is in P** — one literal fewer per clause moves it across the line.

### 3. Travelling Salesman Problem (TSP)

- *Decision version* (NP-complete): given cities and distances, is there a route visiting each city once and returning to the start with total length ≤ X?
- *Optimization version* (NP-hard): find the shortest such route.

The number of possible routes grows factorially with the number of cities (n!).

### 4. Knapsack

- *Decision version* (NP-complete): given items with weights and values, is there a subset with total weight ≤ W and total value ≥ V?
- *Optimization version* (NP-hard): maximise total value without exceeding the weight limit.

### 5. Subset Sum — NP-complete

Given a set of integers, is there a subset summing exactly to a target T? The simplest NP-complete problem to state, and a common reduction source.

### 6. Graph Colouring — NP-complete

Can every vertex be coloured using ≤ k colours so that no two adjacent vertices share a colour? NP-complete for k ≥ 3; **in P for k = 2**, where it is just a bipartiteness check ([`9a_graphs_bfs_dfs.md`](../09_graphs/9a_graphs_bfs_dfs.md)).

### 7. Hamiltonian Cycle — NP-complete

Does the graph contain a cycle visiting every vertex exactly once? TSP is essentially the weighted version of this. Note the contrast with the **Eulerian** cycle — visiting every *edge* once — which is in P, decided by checking vertex degrees.

### 8. Clique — NP-complete

Given a graph and a number k, is there a set of k vertices with every pair connected?

### 9. Vertex Cover — NP-complete

Find the smallest set of vertices touching every edge.

### 10. Independent Set — NP-complete

Find the largest set of vertices with no edges between them. Clique, Vertex Cover and Independent Set are the same problem in three forms, each reducible to the others in a few lines.

### 11. Job Scheduling — NP-hard

Given jobs, machines and durations, schedule them to minimise total completion time or lateness. An optimization problem, hence NP-hard rather than NP-complete.

### 12. Bin Packing — NP-hard

Pack items of differing sizes into the fewest fixed-capacity bins. Practically important, and where approximation algorithms earn their keep.

### Quick classification

| Problem | Class | Note |
|---|---|---|
| sorting, shortest path, matching | **P** | efficiently solvable |
| 2-SAT, bipartite check, Eulerian cycle | **P** | the easy neighbours of hard problems |
| SAT, 3-SAT, Subset Sum, Clique | **NP-complete** | decision form, verifiable |
| Hamiltonian cycle, Graph colouring (k≥3) | **NP-complete** | |
| TSP / Knapsack, optimization form | **NP-hard** | not in NP: optimality is not quickly verifiable |
| Job scheduling, bin packing | **NP-hard** | optimization |
| halting problem | **NP-hard** | undecidable, not in NP |

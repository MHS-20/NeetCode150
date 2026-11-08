# Practical Coding Problems

Exercises for interviews that are not about algorithms: the task is a small program with a spec that grows in stages. The interviewer reveals stage 2 after stage 1 works, and so on. What is judged is whether the code stays correct and easy to extend as the stages arrive: parsing and validation, clear data structures, edge cases, and tests.

Each exercise has:

- `README.md`: the spec, with all its stages. Read one stage at a time to practise as in an interview.
- one solution covering every stage;
- tests grouped by stage, so a later stage cannot silently break an earlier one.

## Business logic (Python)

Payment-company style: transactions, limits, conversions.

| Exercise | Stages |
|---|---|
| [Ledger](business_logic/ledger/) | balances, malformed lines, fees, no overdraft |
| [Rate limiter](business_logic/rate_limiter/) | counting, rolling window, per-endpoint limits, blocking |
| [Currency conversion](business_logic/currency_conversion/) | direct rates, inverse rates, multi-hop, best rate within 3 hops |

Run the tests in an exercise's folder with `python3 test_<name>.py`, or `pytest`.

## Storage (Java)

Database-company style: key-value stores, transactions, caches, on-disk structures. Each solution is a single Java program whose `main` runs the checks: `java <Name>.java`.

[storage/](storage/) is empty for now.

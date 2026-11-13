# Low-Level Design Problems

Object-oriented design problems of the kind asked in LLD or machine-coding rounds: design the classes for a parking lot, an elevator or a booking system, then extend the design when a new requirement arrives. The concepts (SOLID, class diagrams, patterns, concurrency) are in the [object-oriented design lessons](../00_docs/16_object_oriented_design/).

These differ from the [practical problems](../20_practical/), which are judged on a program that stays correct as a spec grows. Here the class model is what is judged, and the tests only check that a later stage does not break an earlier one.

## Format

Each problem folder has:

- `README.md`: the requirements in three stages, then the design. Read one stage at a time to practise as in an interview.
- one Java file with the solution for every stage, and a `main` that runs checks grouped by stage. Run it with `java <Name>.java` (Java 21 or later, no build tool).

The stages follow the same shape in every problem:

1. **Core model.** The entities and the main flow.
2. **Extension.** A new type or rule that should need a new class, not edits across existing ones.
3. **Concurrency or a hard rule.** Two users acting at once, or a constraint that cuts across classes.

The tests call the public API only (park, book, split), not internal classes, so the design can be refactored without rewriting them. About three to six checks per stage is enough.

## README template

```markdown
# <Problem>

<One sentence: what the system does.>

## Stages

1. **Core model.** ...
2. **Extension.** ...
3. **Concurrency.** ...

## Entities

<Classes and what each one owns.>

## Class diagram

<Text diagram.>

## Patterns used

<Pattern, where, and which stage required it. Link to the lesson.>

## Design notes

<Choices and the alternative each one rejects, with its concrete failure.>

## Compared with other solutions

<Differences from the awesome-low-level-design version, after solving it.>

## Files

`<Name>.java`: the solution, with checks for each stage in `main`.
```

## Problems

Rate limiter, LRU cache and the key-value store with transactions are in [practical](../20_practical/) and are not repeated here.

| Problem | Level | Stages | Status |
|---|---|---|---|
| Parking lot | Easy | spots and tickets, vehicle types and pricing, concurrent entry | planned |
| Vending machine | Easy | selection and payment, change and states, restocking | planned |
| Tic-tac-toe | Easy | board and turns, n×n and k in a row, undo | planned |
| Library management | Easy | books and loans, reservations, fines | planned |
| Elevator system | Medium | one car, several cars and scheduling, concurrent requests | planned |
| Snake and ladder | Medium | board and players, custom dice, several games at once | planned |
| Splitwise | Medium | equal splits and balances, exact and percentage splits, simplifying debts | planned |
| Pub-sub | Medium | topics and subscribers, filters, concurrent publishers | planned |
| Movie booking | Hard | shows and seats, pricing tiers, two users on one seat | planned |
| Chess | Hard | board and moves, check and checkmate, undo | planned |
| Ride sharing | Hard | riders and drivers, matching strategy, surge pricing | planned |
| Food delivery | Hard | restaurants and orders, order states, assigning couriers | planned |

When a problem is solved, its folder is added and its row links to it.

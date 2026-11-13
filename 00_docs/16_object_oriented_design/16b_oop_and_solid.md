# OOP Principles and SOLID

Encapsulation, abstraction, inheritance and polymorphism describe what a class can do; the five SOLID principles describe how classes should depend on each other so that a change stays local. Each principle below comes with a short Java example that violates it and the fixed version, both from the same parking-lot domain used in `21_lld`.

> Draft: the sections below are outlined, not written yet.

## The four OOP pillars

<!-- One paragraph and one snippet each. Composition over inheritance, with the case where inheritance is right (a true is-a with substitutable behaviour). -->

## Single responsibility

<!-- Violation: ParkingLot computing fees and printing tickets. Fix: FeeCalculator, TicketPrinter. -->

## Open/closed

<!-- Violation: switch on vehicle type in the fee code. Fix: a PricingStrategy per type. -->

## Liskov substitution

<!-- Violation: a subclass that throws on an inherited method. State the concrete failure in the caller. -->

## Interface segregation

<!-- Violation: one fat Machine interface. Fix: small role interfaces. -->

## Dependency inversion

<!-- Violation: ParkingLot creating its own payment gateway. Fix: inject an interface; this is what makes the stage tests possible. -->

## Sources

<!-- Cite only what was read: R. C. Martin's SOLID articles, refactoring.guru. -->

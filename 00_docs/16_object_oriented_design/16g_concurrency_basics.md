# Concurrency for LLD

LLD rounds often end with "now two users book the last seat at the same time". The answer needs a named shared state, the race on it, and the smallest lock or atomic operation that removes the race. This page covers the Java tools for that and the classic exercises that use them.

> Draft: the sections below are outlined, not written yet.

## Races and critical sections

<!-- Worked example: two threads both read "1 seat left" and both book it. Show the interleaving. -->

## Locks, synchronized and atomics

<!-- synchronized, ReentrantLock, AtomicInteger/compareAndSet; lock granularity (per show vs per seat). -->

## Bounded blocking queue and producer-consumer

<!-- With wait/notify and with Condition; then java.util.concurrent.ArrayBlockingQueue. -->

## Reader-writer locks

<!-- When reads dominate; ReentrantReadWriteLock. -->

## Testing concurrent code

<!-- Run many threads against the invariant, CountDownLatch to start them together; a passing run is evidence, not proof. -->

## LeetCode concurrency problems

<!-- Print in Order, Print FooBar Alternately, Building H2O, Dining Philosophers: check which are free before listing. -->

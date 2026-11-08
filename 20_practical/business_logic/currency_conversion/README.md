# Currency Conversion

Input: rate lines `FROM,TO,rate` (for example `USD,EUR,0.92`) and query lines `amount FROM TO`. Malformed lines of either kind are reported and skipped. For each query, print the converted amount, or `N/A` if no conversion is possible. Converting a currency to itself gives the same amount.

## Stages

1. **Direct rates.** Use only the rates given.
2. **Inverse rates.** A rate `A,B,r` also allows converting `B` to `A` at `1/r`, unless an explicit `B,A` rate is given.
3. **Multi-hop.** Convert through other currencies. Use the path with the fewest conversions.
4. **Best rate.** Among all paths of at most 3 conversions, use the one that gives the most money. Round results to 4 decimals.

## Files

- `currency_conversion.py`: the solution for all four stages. `Converter.bfs` gives the fewest-hops rate of stage 3; `convert` uses the best-rate search of stage 4, which covers the earlier stages.
- `test_currency_conversion.py`: tests grouped by stage. Run with `python3 test_currency_conversion.py` or `pytest`.

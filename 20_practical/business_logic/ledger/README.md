# Ledger

Input: lines of the form `timestamp,from,to,amount_cents,currency`, processed in order. An empty `from` is a deposit: money enters the system and no account is debited.

## Stages

1. **Balances.** Apply every transfer and print each account's final balance in USD, sorted by account name.
2. **Malformed lines.** Skip lines with the wrong number of fields, a non-integer amount or a negative amount. Count them and print the count at the end.
3. **Fees.** A transfer above 100000 cents pays a 1% fee, rounded down. The receiver gets the amount minus the fee, and the fee goes to the account `FEES`.
4. **No overdraft.** An account may never go below 0. Reject a transfer that would overdraw the sender, apply nothing for it, and print the timestamps of the rejected transfers.

## Files

- `ledger.py`: the solution for all four stages.
- `test_ledger.py`: tests grouped by stage. Run with `python3 test_ledger.py` or `pytest`.

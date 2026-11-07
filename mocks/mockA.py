# Mock A — Ledger (original practice task)
#
# Input: lines `timestamp,from,to,amount_cents,currency`.
# 1. Parse and print each account's final balance in USD only, sorted by account.
# 2. Skip malformed lines (wrong field count, non-integer amount, negative amount); count and report them.
# 3. Add a fee rule: transfers above 100000 cents pay 1% fee (rounded down) to account `FEES`.
# 4. An account may never go below 0: reject a transfer that would overdraw it, and output rejected transaction timestamps.

from collections import defaultdict
from dataclasses import dataclass


@dataclass
class Txn:
    ts: str
    frm: str
    to: str
    amount: int
    currency: str


def parse(line):  # part 2: validation lives here
    parts = line.strip().split(",")
    if len(parts) != 5:
        return None
    ts, frm, to, amt, cur = parts
    if not amt.isdigit():  # rejects non-ints and negatives
        return None
    return Txn(ts, frm, to, int(amt), cur)


FEE_THRESHOLD = 100000


class Ledger:
    def __init__(self):
        self.bal = defaultdict(lambda: defaultdict(int))  # bal[acct][cur]
        self.rejected = []

    # empty `from` = deposit: always allowed, no sender to debit
    def transfer(self, t):
        fee = t.amount // 100 if t.amount > FEE_THRESHOLD else 0
        if t.frm != "":
            if self.bal[t.frm][t.currency] < t.amount:
                self.rejected.append(t)
                return
            self.bal[t.frm][t.currency] -= t.amount
        self.bal[t.to][t.currency] += t.amount - fee
        if fee:
            self.bal["FEES"][t.currency] += fee

    def report(self, cur="USD"):
        for acct in sorted(self.bal):
            print(f"{acct}: {self.bal[acct][cur]}")

        for r in self.rejected:  # already in input order; Txn isn't sortable
            print(f"{r.ts} error : insufficient balance")


def mockA(lines):
    ledger, bad = Ledger(), 0
    for l in lines:
        t = parse(l)
        if t is None:
            bad += 1
            continue
        ledger.transfer(t)
    ledger.report()
    print(f"malformed lines: {bad}")
    return ledger, bad


if __name__ == "__main__":
    l, bad = mockA(
        ["1,,A,300000,USD", "2,A,B,200000,USD", "3,B,C,999999,USD", "x,y"]
    )
    assert l.bal["A"]["USD"] == 300000 - 3000 - 200000  # deposit fee, then send
    assert l.bal["B"]["USD"] == 200000 - 2000
    assert l.bal["FEES"]["USD"] == 3000 + 2000
    assert sum(b["USD"] for b in l.bal.values()) == 300000  # money conserved
    assert [t.ts for t in l.rejected] == ["3"] and bad == 1
    print("all tests passed")

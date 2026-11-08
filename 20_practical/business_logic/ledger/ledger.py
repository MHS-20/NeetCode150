from collections import defaultdict
from dataclasses import dataclass


@dataclass
class Txn:
    ts: str
    frm: str
    to: str
    amount: int
    currency: str


def parse(line):  # validation lives here
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


def run(lines):
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

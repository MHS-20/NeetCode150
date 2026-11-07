# Mock C — Currency conversion
#
# Input: rates `USD,EUR,0.92` (one per line) and queries `amount FROM TO`.
# 1. Direct conversions only; output "N/A" if missing.
# 2. Allow the inverse rate automatically.
# 3. Allow multi-hop conversion via BFS over currencies; pick the path with the fewest hops.
# 4. Return the best rate over all paths up to 3 hops, rounded to 4 decimals.

from dataclasses import dataclass
from collections import defaultdict, deque


def parseRates(lines, converter):
    for l in lines:
        parts = l.strip().split(",")
        if len(parts) != 3:
            print(f"MALFORMED LINE: {l}")
            continue
        frm, to, rate = parts
        converter.rates[frm][to] = float(rate)
        # part 2: inverse edge, unless an explicit rate for it exists or comes later
        converter.rates[to].setdefault(frm, 1 / float(rate))


def parseRequests(lines):
    reqs = []
    for l in lines:
        parts = l.strip().split()
        if len(parts) != 3:
            print(f"MALFORMED LINE: {l}")
            continue
        [amt, frm, to] = parts
        reqs.append(Request(frm, to, float(amt)))
    return reqs


@dataclass
class Rate:
    frm: str
    to: str
    rate: float


@dataclass
class Request:
    frm: str
    to: str
    amount: float


MAX_HOPS = 3  # hops = conversions (edges)


class Converter:
    def __init__(self) -> None:
        self.rates = defaultdict(dict)  # frm -> {to: rate}, adjacency map

    def convert(self, req):
        # part 4: best rate over all paths of <= MAX_HOPS conversions
        # (direct and inverse rates are 1-hop paths, so this also covers parts 1-3)
        rate = self.dfs_best(req.frm, req.to, 1.0, set(), MAX_HOPS)
        if rate is None:
            print(f"N/A {req.frm} -> {req.to}")
            return None
        res = round(rate * req.amount, 4)
        print(f"Conversion {req.frm} -> {req.to}: {req.amount} -> {res}")
        return res

    def bfs(self, frm, to):
        """Part 3: rate along the path with the fewest hops, None if unreachable."""
        if frm == to:
            return 1.0
        q = deque([(frm, 1.0)])
        seen = {frm}
        while q:
            cur, rt = q.popleft()
            for nxt_cur, rate in self.rates.get(cur, {}).items():
                if nxt_cur == to:
                    return rt * rate
                if nxt_cur not in seen:
                    seen.add(nxt_cur)
                    q.append((nxt_cur, rt * rate))
        return None

    def dfs_best(self, frm, to, rt, seen, hops):
        """Best rate from frm to `to` using at most `hops` conversions; None if unreachable."""
        if frm == to:
            return rt
        if hops == 0:
            return None
        seen.add(frm)
        best = None
        for nxt_cur, rate in self.rates.get(frm, {}).items():
            if nxt_cur in seen:
                continue
            res = self.dfs_best(nxt_cur, to, rt * rate, seen, hops - 1)
            if res is not None and (best is None or res > best):
                best = res
        seen.remove(frm)  # backtrack: frm is free for other paths
        return best


def mockC(rates, requests):
    converter = Converter()
    parseRates(rates, converter)
    reqs = parseRequests(requests)
    return [converter.convert(req) for req in reqs]


if __name__ == "__main__":
    rates = ["USD,EUR,0.5", "EUR,GBP,0.8", "JPY,CHF,0.01", "bad line"]
    queries = [
        "100 USD EUR",  # direct
        "100 EUR USD",  # inverse (part 2)
        "100 USD GBP",  # 2 hops (part 3)
        "100 GBP USD",  # 2 inverse hops
        "100 USD USD",  # same currency
        "100 USD CHF",  # disconnected -> N/A
        "100 USD XXX",  # unknown currency -> N/A
        "100 USD",  # malformed, skipped
    ]
    res = mockC(rates, queries)
    expected = [50.0, 200.0, 40.0, 250.0, 100.0, None, None]
    assert len(res) == len(expected), res
    for got, exp in zip(res, expected):
        assert (got is None and exp is None) or round(got, 4) == exp, (got, exp)

    # part 4: best rate wins over fewest hops
    rates = ["USD,EUR,0.5", "EUR,GBP,0.8", "USD,GBP,0.39"]
    c = Converter()
    parseRates(rates, c)
    assert round(c.bfs("USD", "GBP"), 4) == 0.39  # BFS: 1 hop, worse rate
    res = mockC(rates, ["100 USD GBP", "100 GBP USD"])
    assert res == [40.0, 256.4103], res  # via EUR 0.4 > 0.39; direct 1/0.39 > 2.5

    # part 4: hop limit. A->E needs 4 hops; a short bad path vs a long good one
    rates = ["A,B,1", "B,C,1", "C,D,1", "D,E,2", "A,D,0.5", "C,X,3"]
    res = mockC(rates, ["1 A E", "1 A D", "1 A X"])
    # A->E: A,D,E = 2 hops (0.5*2=1.0); A,B,C,D,E would be 4 hops (2.0), too long
    # A->D: A,B,C,D = 3 hops (1.0) beats direct 0.5
    # A->X: A,B,C,X = 3 hops (3.0)
    assert res == [1.0, 1.0, 3.0], res

    # part 4: rounding to 4 decimals
    assert mockC(["USD,EUR,0.123456789"], ["1 USD EUR"]) == [0.1235]
    print("all tests passed")

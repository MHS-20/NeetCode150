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
        # inverse edge, unless an explicit rate for it exists or comes later
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
        # best rate over all paths of <= MAX_HOPS conversions
        # direct and inverse rates are 1-hop paths, so they are covered too
        rate = self.dfs_best(req.frm, req.to, 1.0, set(), MAX_HOPS)
        if rate is None:
            print(f"N/A {req.frm} -> {req.to}")
            return None
        res = round(rate * req.amount, 4)
        print(f"Conversion {req.frm} -> {req.to}: {req.amount} -> {res}")
        return res

    def bfs(self, frm, to):
        """rate along the path with the fewest hops, None if unreachable."""
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


def run(rates, requests):
    converter = Converter()
    parseRates(rates, converter)
    reqs = parseRequests(requests)
    return [converter.convert(req) for req in reqs]

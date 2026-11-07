# Mock B — Rate limiter / log processor
#
# Input: lines `epoch_seconds user endpoint`.
# 1. Per user, count requests per endpoint; print the top 3 endpoints overall.
# 2. Limit: max N requests per user in any rolling 60 s window; output each request as ALLOW or DENY.
# 3. Different limits per endpoint from a config string `endpoint:limit,endpoint:limit` (default N).
# 4. Burst rule: a user denied 3 times in 10 s is blocked for 5 minutes.

from collections import Counter, defaultdict, deque
from dataclasses import dataclass

WINDOW = 60  # seconds, rolling rate-limit window
BURST_WINDOW = 10  # seconds
BURST_DENIES = 3  # denies within BURST_WINDOW that trigger a block
BLOCK = 5 * 60  # seconds


@dataclass
class Request:
    ts: int
    user: str
    endpoint: str


def parse(line):
    """Input line: 'epoch_seconds user endpoint'. Returns None if malformed."""
    parts = line.split()
    if len(parts) != 3 or not parts[0].isdigit():
        return None
    ts, user, endpoint = parts
    return Request(int(ts), user, endpoint)


def parse_limits(limits, n):
    """'endpoint:limit,endpoint:limit' -> endpoint -> limit; unknown endpoints get n."""
    config = defaultdict(lambda: n)
    for part in limits.split(","):
        if not part:  # empty config string
            continue
        k, _, v = part.partition(":")
        config[k] = int(v)
    return config


class RateLimiter:
    def __init__(self, limits):
        self.limits = limits  # endpoint -> limit
        self.hits = defaultdict(deque)  # (user, endpoint) -> timestamps
        self.denies = defaultdict(deque)  # user -> timestamps of recent DENIED requests
        self.blocked_until = {}  # user -> ts when the block ends
        self.user_endpoints = defaultdict(Counter)  # user -> endpoint -> count
        self.endpoint_totals = Counter()  # endpoint -> count, all users

    def record(self, req):
        """count every request, allowed or not."""
        self.user_endpoints[req.user][req.endpoint] += 1
        self.endpoint_totals[req.endpoint] += 1

    def allow(self, req):
        """True = ALLOW, False = DENY."""
        # blocked users are denied first; these denies don't extend the block
        if self.blocked_until.get(req.user, -1) > req.ts:
            return False

        # rolling window per (user, endpoint), limit per endpoint
        q = self.hits[(req.user, req.endpoint)]
        while q and q[0] <= req.ts - WINDOW:
            q.popleft()
        if len(q) < self.limits[req.endpoint]:
            q.append(req.ts)  # only allowed requests use up the quota
            return True

        # a user denied BURST_DENIES times in BURST_WINDOW s is blocked
        r = self.denies[req.user]
        r.append(req.ts)
        while r and r[0] <= req.ts - BURST_WINDOW:
            r.popleft()
        if len(r) >= BURST_DENIES:
            self.blocked_until[req.user] = req.ts + BLOCK
            r.clear()
        return False

    def top_endpoints(self, k=3):
        return self.endpoint_totals.most_common(k)


def mockB(lines, n, limits=""):
    limiter, decisions, bad = RateLimiter(parse_limits(limits, n)), [], 0
    for line in lines:
        req = parse(line)
        if req is None:
            bad += 1
            continue
        limiter.record(req)
        d = "ALLOW" if limiter.allow(req) else "DENY"
        decisions.append(d)
        print(f"{req.ts} {req.user} {req.endpoint} {d}")
    for ep, c in limiter.top_endpoints():
        print(f"{ep}: {c}")
    print(f"malformed lines: {bad}")
    return limiter, decisions, bad


if __name__ == "__main__":
    # parts 1-3: default N=2, login limited to 1
    lines = [
        "0 alice login",  # ALLOW
        "5 alice login",  # DENY: login limit is 1
        "6 alice search",  # ALLOW: search has its own window (default 2)
        "7 alice search",  # ALLOW
        "8 alice search",  # DENY: 3rd search in 60 s
        "9 bob login",  # ALLOW: bob has his own quota
        "60 alice login",  # ALLOW: ts 0 left the window (0 <= 60-60)
        "bad line",
        "x alice login",
    ]
    l, d, bad = mockB(lines, n=2, limits="login:1")
    assert d == ["ALLOW", "DENY", "ALLOW", "ALLOW", "DENY", "ALLOW", "ALLOW"], d
    assert bad == 2
    assert l.top_endpoints() == [("login", 4), ("search", 3)], l.top_endpoints()
    assert l.user_endpoints["alice"] == {"login": 3, "search": 3}
    assert "alice" not in l.blocked_until  # only 2 denies, no block

    # part 4: N=1, 3 denies in 10 s -> blocked for 300 s
    lines = [
        "0 u a",  # ALLOW
        "1 u a",  # DENY 1
        "2 u a",  # DENY 2
        "3 u a",  # DENY 3 -> blocked until 303
        "100 u b",  # DENY: blocked, even on another endpoint
        "302 u b",  # DENY: still blocked
        "303 u b",  # ALLOW: block over
    ]
    l, d, _ = mockB(lines, n=1)
    assert d == ["ALLOW", "DENY", "DENY", "DENY", "DENY", "DENY", "ALLOW"], d
    assert l.blocked_until["u"] == 303

    cfg = parse_limits("login:5,search:100", 7)
    assert cfg["login"] == 5 and cfg["search"] == 100 and cfg["other"] == 7
    print("all tests passed")

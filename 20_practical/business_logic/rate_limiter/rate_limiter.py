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


def run(lines, n, limits=""):
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

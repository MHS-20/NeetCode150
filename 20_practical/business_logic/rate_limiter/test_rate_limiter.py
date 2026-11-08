from rate_limiter import parse, parse_limits, run

LINES = [
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


def test_stage1_counting():
    l, _, bad = run(LINES, n=2, limits="login:1")
    assert bad == 2
    assert parse("x alice login") is None
    assert l.top_endpoints() == [("login", 4), ("search", 3)]
    assert l.user_endpoints["alice"] == {"login": 3, "search": 3}


def test_stage2_rolling_window():
    _, d, _ = run(["0 u a", "1 u a", "2 u a", "59 u a", "60 u a"], n=2)
    # third request denied; at 60 the request from 0 has left the window
    assert d == ["ALLOW", "ALLOW", "DENY", "DENY", "ALLOW"]


def test_stage3_per_endpoint_limits():
    _, d, _ = run(LINES, n=2, limits="login:1")
    assert d == ["ALLOW", "DENY", "ALLOW", "ALLOW", "DENY", "ALLOW", "ALLOW"]
    cfg = parse_limits("login:5,search:100", 7)
    assert cfg["login"] == 5 and cfg["search"] == 100 and cfg["other"] == 7
    assert parse_limits("", 3)["any"] == 3


def test_stage4_blocking():
    lines = [
        "0 u a",  # ALLOW
        "1 u a",  # DENY 1
        "2 u a",  # DENY 2
        "3 u a",  # DENY 3 -> blocked until 303
        "100 u b",  # DENY: blocked, even on another endpoint
        "302 u b",  # DENY: still blocked
        "303 u b",  # ALLOW: block over
    ]
    l, d, _ = run(lines, n=1)
    assert d == ["ALLOW", "DENY", "DENY", "DENY", "DENY", "DENY", "ALLOW"]
    assert l.blocked_until["u"] == 303
    l, _, _ = run(LINES, n=2, limits="login:1")
    assert "alice" not in l.blocked_until  # only 2 denies, no block


if __name__ == "__main__":
    for name, f in list(globals().items()):
        if name.startswith("test_"):
            f()
    print("all tests passed")

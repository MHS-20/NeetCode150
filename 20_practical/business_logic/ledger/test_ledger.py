from ledger import Ledger, parse, run


def test_stage1_balances():
    l, _ = run(["1,,A,500,USD", "2,A,B,200,USD", "3,,C,100,EUR"])
    assert l.bal["A"]["USD"] == 300
    assert l.bal["B"]["USD"] == 200
    assert l.bal["C"]["USD"] == 0  # EUR is tracked but not reported


def test_stage2_malformed():
    assert parse("x,y") is None  # wrong field count
    assert parse("1,A,B,1.5,USD") is None  # not an integer
    assert parse("1,A,B,-5,USD") is None  # negative
    _, bad = run(["x,y", "1,,A,10,USD", "1,A,B,abc,USD"])
    assert bad == 2


def test_stage3_fees():
    l, _ = run(["1,,A,300000,USD", "2,A,B,200000,USD"])
    assert l.bal["A"]["USD"] == 300000 - 3000 - 200000  # deposit fee, then send
    assert l.bal["B"]["USD"] == 200000 - 2000
    assert l.bal["FEES"]["USD"] == 3000 + 2000
    assert sum(b["USD"] for b in l.bal.values()) == 300000  # money conserved
    l, _ = run(["1,,A,100000,USD"])  # exactly the threshold: no fee
    assert l.bal["A"]["USD"] == 100000 and l.bal["FEES"]["USD"] == 0


def test_stage4_no_overdraft():
    l, bad = run(["1,,A,300000,USD", "2,A,B,200000,USD", "3,B,C,999999,USD", "x,y"])
    assert [t.ts for t in l.rejected] == ["3"] and bad == 1
    assert l.bal["C"]["USD"] == 0  # nothing applied for the rejected transfer


if __name__ == "__main__":
    for name, f in list(globals().items()):
        if name.startswith("test_"):
            f()
    print("all tests passed")

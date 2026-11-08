from currency_conversion import Converter, parseRates, run


def check(res, expected):
    assert len(res) == len(expected), res
    for got, exp in zip(res, expected):
        assert (got is None and exp is None) or round(got, 4) == exp, (got, exp)


def test_stage1_direct():
    check(run(["USD,EUR,0.5", "bad line"], ["100 USD EUR", "100 USD USD", "100 USD XXX", "100 USD"]),
          [50.0, 100.0, None])


def test_stage2_inverse():
    check(run(["USD,EUR,0.5"], ["100 EUR USD"]), [200.0])
    check(run(["USD,EUR,0.5", "EUR,USD,3"], ["100 EUR USD"]), [300.0])  # explicit rate wins


def test_stage3_multi_hop():
    rates = ["USD,EUR,0.5", "EUR,GBP,0.8", "JPY,CHF,0.01"]
    check(run(rates, ["100 USD GBP", "100 GBP USD", "100 USD CHF"]), [40.0, 250.0, None])
    c = Converter()
    parseRates(["USD,EUR,0.5", "EUR,GBP,0.8", "USD,GBP,0.39"], c)
    assert round(c.bfs("USD", "GBP"), 4) == 0.39  # fewest hops, even with a worse rate


def test_stage4_best_rate():
    assert run(["USD,EUR,0.5", "EUR,GBP,0.8", "USD,GBP,0.39"], ["100 USD GBP", "100 GBP USD"]) == [40.0, 256.4103]
    # hop limit: A->E through B, C, D would be 4 conversions
    rates = ["A,B,1", "B,C,1", "C,D,1", "D,E,2", "A,D,0.5", "C,X,3"]
    assert run(rates, ["1 A E", "1 A D", "1 A X"]) == [1.0, 1.0, 3.0]
    assert run(["USD,EUR,0.123456789"], ["1 USD EUR"]) == [0.1235]


if __name__ == "__main__":
    for name, f in list(globals().items()):
        if name.startswith("test_"):
            f()
    print("all tests passed")

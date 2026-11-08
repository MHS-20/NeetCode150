# Rate Limiter

Input: lines of the form `epoch_seconds user endpoint`, in time order. Lines that do not have three fields, or whose time is not an integer, are skipped and counted.

## Stages

1. **Counting.** Count requests per user and endpoint, and print the three endpoints with the most requests overall.
2. **Rate limit.** A user may make at most `N` requests to an endpoint in any rolling 60-second window. Print each request with `ALLOW` or `DENY`. A request at time `t` leaves the window at `t + 60`. Only allowed requests use up the quota.
3. **Per-endpoint limits.** Limits come from a config string `endpoint:limit,endpoint:limit`. Endpoints not listed use `N`.
4. **Blocking.** A user denied 3 times within 10 seconds is blocked for 5 minutes, on every endpoint. Requests during the block are denied and do not extend it.

## Files

- `rate_limiter.py`: the solution for all four stages.
- `test_rate_limiter.py`: tests grouped by stage. Run with `python3 test_rate_limiter.py` or `pytest`.

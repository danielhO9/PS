#include <bits/stdc++.h>
using namespace std;
int N, W, enemy[20001], cache[4][4][10001], ans;
bool type[4][2] = {{true, true}, {false, true}, {true, false}, {false, false}};

bool available(int b, int h, int n) {
    if (n > N) return false;
    if (n == N && !type[b][h]) return false;
    return true;
}

int matchCache(int f, int b, int n) {
    if (n == N + 1) return 0;
    int& ret = cache[f][b][n];
    if (ret != -1) return ret;
    ret = 2 * N;
    if (f == 0) {
        if (!available(b, 0, n)) return ret = matchCache(1, b, n);
        if (!available(b, 1, n)) return ret = matchCache(2, b, n);
        ret = min(ret, matchCache(2, b, n) + 1);
        ret = min(ret, matchCache(1, b, n) + 1);
        if (enemy[n] + enemy[n + N] <= W) ret = min(ret, matchCache(3, b, n) + 1);
        if (available(b, 1, n + 1) && enemy[n + N] + enemy[n + N + 1] <= W) ret = min(ret, matchCache(2, b, n + 1) + 2);
        if (available(b, 0, n + 1) && enemy[n] + enemy[n + 1] <= W) ret = min(ret, matchCache(1, b, n + 1) + 2);
        if (available(b, 1, n + 1) && enemy[n + N] + enemy[n + N + 1] <= W && available(b, 0, n + 1) && enemy[n] + enemy[n + 1] <= W) {
            ret = min(ret, matchCache(3, b, n + 1) + 2);
        }
    } else if (f == 1) {
        if (!available(b, 1, n)) return matchCache(3, b, n);
        ret = min(ret, matchCache(3, b, n) + 1);
        if (available(b, 1, n + 1) && enemy[n + N] + enemy[n + N + 1] <= W) ret = min(ret, matchCache(2, b, n + 1) + 1);
    } else if (f == 2) {
        if (!available(b, 0, n)) return matchCache(3, b, n);
        ret = min(ret, matchCache(3, b, n) + 1);
        if (available(b, 0, n + 1) && enemy[n] + enemy[n + 1] <= W) ret = min(ret, matchCache(1, b, n + 1) + 1);
    } else {
        return ret = matchCache(0, b, n + 1);
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    for (int i = 0; i < T; ++i) {
        cin >> N >> W;
        for (int i = 1; i <= 2 * N; ++i) cin >> enemy[i];
        ans = 2 * N;
        if (enemy[1] + enemy[N] <= W && enemy[N + 1] + enemy[2 * N] <= W) { memset(cache, -1, sizeof(cache)); ans = min(ans, matchCache(3, 3, 1) + 2); }
        if (enemy[1] + enemy[N] <= W) { memset(cache, -1, sizeof(cache)); ans = min(ans, matchCache(1, 1, 1) + 1); }
        if (enemy[N + 1] + enemy[2 * N] <= W) { memset(cache, -1, sizeof(cache)); ans = min(ans, matchCache(2, 2, 1) + 1); }
        memset(cache, -1, sizeof(cache)); ans = min(ans, matchCache(0, 0, 1));
        cout << ans << "\n";
    }
    return 0;
}
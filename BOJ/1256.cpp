#include <bits/stdc++.h>
using namespace std;
int N, M, K, cache[201][101];
string ans = "";

int matchCache(int n, int r) {
    if (n == 0) return 0;
    if (r == 0 || n == r) return 1;
    int& ret = cache[n][r];
    if (ret != -1) return ret;
    ret = matchCache(n - 1, r - 1) + matchCache(n - 1, r);
    if (ret > 1e9) ret = 1e9 + 1;
    return ret;
}

void solve(int a, int z, int k) {
    if (a == 0) {
        for (int i = 0; i < z; ++i) ans += "z";
        return;
    }
    if (z == 0) {
        for (int i = 0; i < a; ++i) ans += "a";
        return;
    }
    if (matchCache(a + z - 1, z) < k) {
        ans += "z";
        solve(a, z - 1, k - matchCache(a + z - 1, z));
    } else {
        ans += "a";
        solve(a - 1, z, k);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M >> K;
    memset(cache, -1, sizeof(cache));
    if (matchCache(N + M, M) < K) cout << "-1";
    else { solve(N, M, K); cout << ans; }
    return 0;
}
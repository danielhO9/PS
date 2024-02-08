#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL N, K, M, cache[2000][2000];

LL matchCache(LL n, LL r) {
    if (r == 0 || n == r) return 1;
    if (n < r) return 0;
    LL& ret = cache[n][r];
    if (ret != -1) return ret;
    ret = ((matchCache(n - 1, r) + matchCache(n - 1, r - 1)) % M);
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> K >> M;
    LL ans = 1;
    memset(cache, -1, sizeof(cache));
    while (N != 0) {
        ans *= matchCache(N % M, K % M);
        ans %= M;
        N /= M; K /= M;
    }
    cout << ans;
    return 0;
}
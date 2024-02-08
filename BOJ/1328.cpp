#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL cache[101][101][101];
LL N, L, R;

LL dp(LL N, LL L, LL R) {
    LL& ret = cache[N][L][R];
    if (ret != -1) return ret;
    if (N + 1 == L + R && (L == 1 || R == 1)) return ret = 1;
    if (N + 1 < L + R) return ret = 0;
    if (N == 0 || L == 0 || R == 0) return ret = 0;
    return ret = (dp(N - 1, L, R) * (N - 2) + dp(N - 1, L - 1, R) + dp(N - 1, L, R - 1)) % 1000000007;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    memset(cache, -1, sizeof(cache));
    cin >> N >> L >> R;
    cout << dp(N, L, R);
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL cache[21][21][21];
LL N, L, R;

LL matchCache(LL N, LL L, LL R) {
    LL& ret = cache[N][L][R];
    if (ret != -1) return ret;
    if (N + 1 == L + R && (L == 1 || R == 1)) return ret = 1;
    if (N + 1 < L + R) return ret = 0;
    if (N == 0 || L == 0 || R == 0) return ret = 0;
    return ret = (matchCache(N - 1, L, R) * (N - 2) + matchCache(N - 1, L - 1, R) + matchCache(N - 1, L, R - 1));
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    memset(cache, -1, sizeof(cache));
    int T; cin >> T;
    for (int i = 0; i < T; ++i) {
        cin >> N >> L >> R;
        memset(cache, -1, sizeof(cache));
        cout << matchCache(N, L, R) << "\n";
    }
    return 0;
}
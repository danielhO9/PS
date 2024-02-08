#include <bits/stdc++.h>
using namespace std;
int N, cache[65536], P, p, cost[16][16];

int dp(int query) {
    int& ret = cache[query];
    if (ret != 600) return ret;
    p = 0; for (int i = 0; i < N; ++i) if (query == (query | 1 << i)) ++p;
    if (p >= P) return ret = 0;
    for (int i = 0; i < N; ++i) if (query == (query | 1 << i)) {
        for (int j = 0; j < N; ++j) if (query != (query | 1 << j)) {
            ret = min(ret, cost[i][j] + dp(query | 1 << j));
        }
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    for (int i = 0; i < 65536; ++i) cache[i] = 600;
    cin >> N;
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> cost[i][j];
    string now; cin >> now; int query = 0;
    for (int i = 0; i < N; ++i) if (now[i] == 'Y') query |= 1 << i;
    cin >> P;
    if (query == 0 && P == 0) cout << 0;
    else if (query == 0 && P != 0) cout << -1;
    else cout << dp(query);
    return 0;
}
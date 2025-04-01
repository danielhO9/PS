#include <bits/stdc++.h>
using namespace std;

int K, N;
int C[20][20];
int cache[1 << 20];

int matchCache(int mask) {
    int& ret = cache[mask];
    if (ret != -1) return ret;
    if (mask == (1 << N) - 1) return ret = 0;
    ret = INT32_MAX;
    for (int i = 0; i < N; ++i) if (!((mask >> i) & 1)) {
        for (int j = 0; j < N; ++j) if ((mask >> j) & 1) {
            ret = min(ret, matchCache(mask ^ (1 << i)) + C[i][j]);
        }
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> K;
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> C[i][j];
    memset(cache, -1, sizeof(cache));
    int ans = INT32_MAX;
    for (int i = 0; i < (1 << N); ++i) if (__builtin_popcount(i) <= K) {
        ans = min(ans, matchCache(i));
    }
    cout << ans;
}
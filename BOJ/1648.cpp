#include <bits/stdc++.h>
using namespace std;
int N, M, cache[14 * 14][1 << 14];

int matchCache(int p, int f) {
    if (N * M - p <= M && f == (1 << (N * M - p)) - 1) return 1;
    int& ret = cache[p][f];
    if (ret != -1) return ret;
    if (f == (f | (1 << 0))) return ret = matchCache(p + 1, f >> 1);
    ret = 0;
    if ((p % M) != (M - 1) && p < N * M - 1 && f != (f | (1 << 1))) { ret += matchCache(p + 2, f >> 2); ret %= 9901; }
    if ((p + M) < N * M) { ret += matchCache(p + 1, ((f >> 1) | (1 << (M - 1)))); ret %= 9901; }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    memset(cache, -1, sizeof(cache));
    cout << matchCache(0, 0);
    return 0;
}
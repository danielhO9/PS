#include <bits/stdc++.h>
using namespace std;
int N, M;
int location[1001], power[1001], psum[1001], cache[1001][1001];

int matchCache(int p, int n) {
    if (abs(p - n) == N - 1) return 0;
    int& ret = cache[p][n];
    if (ret != -1) return ret;
    ret = (int)1e9;
    int dif = psum[min(p, n) - 1] + psum[N] - psum[max(p, n)];
    if (n <= p) {
        if (n - 1 >= 1) ret = min(ret, matchCache(p, n - 1) + dif * (location[n] - location[n - 1]));
        if (p + 1 <= N) ret = min(ret, matchCache(n, p + 1) + dif * (location[p + 1] - location[n]));
    } else {
        if (p - 1 >= 1) ret = min(ret, matchCache(n, p - 1) + dif * (location[n] - location[p - 1]));
        if (n + 1 <= N) ret = min(ret, matchCache(p, n + 1) + dif * (location[n + 1] - location[n]));
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for (int i = 1; i <= N; ++i) {
        cin >> location[i] >> power[i];
        psum[i] = power[i] + psum[i - 1];
    }
    memset(cache, -1, sizeof(cache));
    cout << matchCache(M, M);
}

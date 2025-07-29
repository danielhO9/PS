#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1999;

ll N, M;
int a[1001];
int c[1001];
int d[1001];
int t[2001];

void kitamasa(ll n, int m) {
    if (n == 1) {
        d[1] = 1;
        for (int i = 2; i <= m; ++i) d[i] = 0;
        return;
    }
    if (n & 1) {
        kitamasa(n ^ 1, m);
        int tmp = d[m];
        for (int i = m; i >= 1; --i) d[i] = (d[i - 1] + c[m - i + 1] * tmp) % MOD;
        return;
    }
    kitamasa(n >> 1, m);
    for (int i = 1; i <= 2 * m; ++i) t[i] = 0;
    for (int i = 1; i <= m; ++i) for (int j = 1; j <= m; ++j) t[i + j] = (t[i + j] + d[i] * d[j]) % MOD;
    for (int i = 2 * m; i > m; --i) for (int j = 1; j <= m; ++j) t[i - j] = (t[i - j] + c[j] * t[i]) % MOD;
    for (int i = 1; i <= m; ++i) d[i] = t[i];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for (int i = 1; i <= N; ++i) {
        if (i == 1) a[i] = 1;
        else a[i] = a[i - 1] * 2 % MOD;
        c[i] = 1;
    }
    c[N] = a[N]; c[N] %= MOD;
    a[N] *= 2; a[N] += MOD - 1; a[N] %= MOD;
    if (M <= N) {
        cout << a[M];
        return 0;
    }
    // for (int i = 1; i <= N; ++i) cout << c[i] << ' ' << a[i] << '\n';
    kitamasa(M, N);
    int ans = 0;
    for (int i = 1; i <= N; ++i) ans = (ans + d[i] * a[i]) % MOD;
    cout << ans;
}
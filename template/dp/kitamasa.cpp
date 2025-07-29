#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1999;

ll a[1001];
ll c[1001];
ll d[1001];
ll t[2001];

void kitamasa(ll n, int m) {
    if (n == 1) {
        d[1] = 1;
        for (int i = 2; i <= m; ++i) d[i] = 0;
        return;
    }
    if (n & 1) {
        kitamasa(n ^ 1, m);
        ll tmp = d[m];
        for (int i = m; i >= 1; --i) d[i] = (d[i - 1] + c[m - i + 1] * tmp) % MOD;
        return;
    }
    kitamasa(n >> 1, m);
    for (int i = 1; i <= 2 * m; ++i) t[i] = 0;
    for (int i = 1; i <= m; ++i) for (int j = 1; j <= m; ++j) t[i + j] = (t[i + j] + d[i] * d[j]) % MOD;
    for (int i = 2 * m; i > m; --i) for (int j = 1; j <= m; ++j) t[i - j] = (t[i - j] + c[j] * t[i]) % MOD;
    for (int i = 1; i <= m; ++i) d[i] = t[i];
}
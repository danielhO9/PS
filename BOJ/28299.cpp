#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 998244353;

ll pow(ll a, ll b) {
    if (b == 0) return 1ll;
    ll h = pow(a, b / 2);
    h = (h * h) % MOD;
    if (b % 2) return (a * h) % MOD;
    return h;
}

ll n;
ll a[200000];
ll inv[5];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (ll i = 2; i <= 4; ++i) inv[i] = pow(i, MOD - 2);
    ll sm = 0;
    for (int i = 0; i < n; ++i) sm += a[i];
    ll ans = 0;
    ll xsm = 0;
    vector<ll> xs;
    for (int i = 0; i < n; ++i) {
        sm -= a[i];
        ll x = (((sm * a[i]) % MOD) * inv[2]) % MOD;
        ll xx = x;
        if (sm > 0) xx += (((((sm * (sm - 1)) % MOD) * a[i]) % MOD) * inv[3]) % MOD, xx %= MOD;
        if (a[i] > 0) xx += (((((a[i] * (a[i] - 1)) % MOD) * sm) % MOD) * inv[3]) % MOD, xx %= MOD;
        if (sm > 0 && a[i] > 0) xx += (((((((a[i] * (a[i] - 1)) % MOD) * sm) % MOD) * inv[4]) % MOD) * (sm - 1))%MOD, xx %= MOD;
        ans += xx;
        ans %= MOD;
        xs.push_back(x);
        xsm += x;
    }
    for (int i = 0; i < n; ++i) {
        ans += (xs[i] * ((xsm - xs[i] + MOD) % MOD)) % MOD;
        ans %= MOD;
    }
    cout << ans;
}
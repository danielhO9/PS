#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 119 * (2 ^ 23) + 1 = 998244353, 원시근: 3
//   7 * (2 ^ 26) + 1 = 469762049, 원시근: 3
//  17 * (2 ^ 27) + 1 = 3221225473, 원시근: 5
const ll _A = 119, _B = 23, _P = _A << _B | 1, _X = 3;
const ll MOD = 998244353;

ll modpow(ll a, ll b, ll mod) {
	if (b == 0) return 1ll;
	ll half = modpow(a, b / 2, mod);
	half = (half * half) % mod;
	if (b % 2 == 0) return half;
	else return (half * a) % mod;
}

void fft(vector<ll>& a, bool inv) {
    ll n = a.size();
    for (ll i = 1, j = 0; i < n; i++) {
        ll bit = n >> 1;
        while (!((j ^= bit) & bit)) bit >>= 1;
        if (i < j) swap(a[i], a[j]);
    }
    for (ll i = 1; i < n; i <<= 1) {
        ll w = modpow(inv ? modpow(_X, _P - 2, _P) : _X, _P / i >> 1, _P);
        for (ll j = 0; j < n; j += i << 1) {
            ll th = 1ll;
            for (ll k = 0; k < i; k++) {
                ll tmp = a[i + j + k] * th % _P;
                a[i + j + k] = a[j + k] - tmp;
				if (a[i + j + k] < 0) a[i + j + k] += _P;
                a[j + k] += tmp;
				if (a[j + k] >= _P) a[j + k] -= _P;
                th = th * w % _P;
            }
        }
    }
    if (inv) {
		ll ninv = modpow(n, _P - 2, _P);
        for (ll i = 0; i < n; i++) a[i] = a[i] * ninv % _P;
    }
}

vector<ll> multiply(vector<ll>& A, vector<ll>& B) {
    vector<ll> a(A.begin(), A.end()), b(B.begin(), B.end());
    ll n = max(a.size(), b.size());
    ll i = 0;
    while ((1 << i) < (n << 1)) i++;
    n = 1 << i;
    a.resize(n);
    b.resize(n);
    fft(a, false);
    fft(b, false);
    for (ll i = 0; i < n; i++) a[i] = a[i] * b[i] % _P;
    fft(a, true);
    vector<ll> ret;
	for (auto i: a) ret.push_back(i);
	while (!ret.empty() && ret.back() == 0) ret.pop_back();
    return ret;
}

ll n;
ll d[100000];

vector<ll> dnc(int l, int r) {
    if (l == r) return {1, (MOD - modpow(d[l], MOD - 2, MOD)) % MOD};
    int m = (l + r) / 2;
    vector<ll> hl = dnc(l, m), hr = dnc(m + 1, r);
    vector<ll> ret = multiply(hl, hr);
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> d[i];
    ll mnd = LLONG_MAX;
    for (int i = 0; i < n; ++i) mnd = min(mnd, d[i]);
    vector<ll> poly = dnc(0, n - 1);
    ll ans = 0;
    ll pd = mnd;
    for (ll i = 0; i <= n; ++i) {
        ans += (((poly[i] * pd) % MOD) * modpow(i + 1, MOD - 2, MOD)) % MOD;
        ans %= MOD;
        pd *= mnd;
        pd %= MOD;
    }
    cout << ans;
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
const ll MOD = 998244353;

const ll _A = 119, _B = 23, _P = _A << _B | 1, _X = 3;

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
		// cout << w << '\n';
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
const ll M = 300005;
pll ran[M];
unordered_map<ll, ll> m;
vector<ll> y, c;
ll in[2*M], out[2*M], cor[2*M];
ll fac[M];
ll inv[M];

void init() {
	fac[0] = 1ll;
	for (ll i = 1; i < M; ++i) {
		fac[i] = fac[i - 1] * i;
		fac[i] %= MOD;
	}
	for (int i = 0; i < M; ++i) {
		inv[i] = modpow(fac[i], MOD - 2, MOD);
	}
}

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> ran[i].first >> ran[i].second;
	for (int i = 0; i < n; ++i) ++ran[i].second;
	set<ll> s;
	for (int i = 0; i < n; ++i) {
		s.insert(ran[i].first);
		s.insert(ran[i].second);
	}
	ll idx = 0;
	for (auto i: s) {
		cor[idx] = i;
		m[i] = idx++;
	}
	for (int i = 0; i < n; ++i) {
		++in[m[ran[i].first]];
		++out[m[ran[i].second]];
	}
	ll cnt = 0;
	for (int i = 0; i < idx; ++i) {
		cnt -= out[i];
		cnt += in[i];
		y.push_back(cnt);
		if (i + 1 == idx) c.push_back(1);
		else c.push_back(cor[i + 1] - cor[i]);
	}
	vector<ll> A(n + 1), B(n + 1);
	for (int i = 0; i < y.size(); ++i) {
		A[y[i]] += (fac[y[i]] * c[i]) % MOD;
		A[y[i]] %= MOD;
	}
	for (int i = 0; i < n + 1; ++i) {
		B[i] = inv[n - i];
	}
	auto res = multiply(A, B);
	for (int i = n + 1; i < 2 * n + 1; ++i) {
		ll tmp = (res[i] * inv[i - n]) % MOD;
		cout << tmp << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	solve();
}
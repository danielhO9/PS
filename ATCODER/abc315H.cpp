#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
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

vector<ll> A, B, C;

void Update(int l1, int r1, int l2, int r2) {
	vector<ll> a(A.begin() + l1, A.begin() + r1);
	vector<ll> b(B.begin() + l2, B.begin() + r2);
	vector<ll> c = multiply(a, b);
	for (int i = 0; i < c.size(); i++) {
        C[l1 + l2 + i] += c[i];
        C[l1 + l2 + i] %= MOD;
    }
}

void Push(ll a, ll b) {
	const ll n = A.size(); A.push_back(a), B.push_back(b);
	const ll s = log2(n + 1);
	const ll k = __builtin_ctz(n + 2 - (1 << s));
	for (ll x = n, y = 0, i = 0; i <= k; i++) {
		Update(x, (x + (1 << i)) % MOD, y, (y + (1 << i)) % MOD);
		if (x != y) Update(y, (y + (1 << i)) % MOD, x, (x + (1 << i)) % MOD);
		x -= 1 << i, y += 1 << i;
        x += MOD; x %= MOD;
        y %= MOD;
	}
}

ll N;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    C.resize(2 * N + 1);
    ll P = 1; Push(1, 1);
	for (int i = 1; i <= N; i++) {
		ll x; cin >> x;
		ll F_i = (x * P) % MOD; Push(F_i, F_i); P += C[i];
        P %= MOD;
		cout << F_i << ' ';
	}

}
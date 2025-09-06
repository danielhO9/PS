#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;

// 119 * (2 ^ 23) + 1 = 998244353, 원시근: 3
//   7 * (2 ^ 26) + 1 = 469762049, 원시근: 3
//  17 * (2 ^ 27) + 1 = 3221225473, 원시근: 5
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
    return ret;
}

ll N, K;
ll a[200001], dp[200001], C[200001];
ll fac[400001], ifac[400001];

void init() {
    fac[0] = 1;
    for (ll i = 1; i <= 400000; ++i) fac[i] = (fac[i - 1] * i) % MOD;
    for (ll i = 0; i <= 400000; ++i) ifac[i] = modpow(fac[i], MOD - 2, MOD);
    for (ll i = 0; i <= 200000; ++i) {
        C[i] = modpow(i + 1, MOD - 2, MOD);
        C[i] *= fac[i * 2]; C[i] %= MOD;
        C[i] *= ifac[i]; C[i] %= MOD;
        C[i] *= ifac[i]; C[i] %= MOD;
    }
}

void dnc(int l, int r) {
    if (l == r) {
        if (l == 0) dp[0] = a[0];
        return;
    }
    int mid = (l + r) / 2;
    dnc(l, mid);
    vector<ll> A(max(1ll, r - K - l + 1)), B(mid - l + 1);
    for (int i = 0; i < A.size(); ++i) A[i] = C[i];
    for (int i = 0; i < B.size(); ++i) B[i] = dp[i + l];
    auto ntt = multiply(A, B);
    for (int i = mid + 1; i <= r; ++i) {
        if (i - K - l >= 0) {
            dp[i] += (ntt[i - K - l] * a[i]) % MOD;
            dp[i] %= MOD;
        }
    }
    dnc(mid + 1, r);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init();
    cin >> N >> K;
    for (int i = 0; i <= N; ++i) cin >> a[i];
    dnc(0, N);
    for (int i = K; i <= N; ++i) cout << dp[i] << ' ';
}
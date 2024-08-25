#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef complex<long double> base;

const long double PI = acos(-1.l);

void fft(vector<base>& a, bool inv) {
    ll n = a.size();
    for (ll i = 1, j = 0; i < n; i++) {
        ll bit = n >> 1;
        while (!((j ^= bit) & bit)) bit >>= 1;
        if (i < j) swap(a[i], a[j]);
    }
    for (ll i = 1; i < n; i <<= 1) {
		vector<base> w(i);
		for (ll j = 0; j < i; ++j) {
			long double x = inv ? PI * j / i : -PI * j / i;
			w[j] = {cos(x), sin(x)};
		}
        for (ll j = 0; j < n; j += i << 1) {
            for (ll k = 0; k < i; k++) {
                base tmp = a[i + j + k] * w[k];
                a[i + j + k] = a[j + k] - tmp;
                a[j + k] += tmp;
            }
        }
    }
    if (inv) {
        for (ll i = 0; i < n; i++) a[i] /= n;
    }
}

vector<ll> multiply(vector<ll>& A, vector<ll>& B) {
    vector<base> a(A.begin(), A.end()), b(B.begin(), B.end());
    ll n = max(a.size(), b.size());
    ll i = 0;
    while ((1ll << i) < (n << 1)) i++;
    n = 1ll << i;
    a.resize(n);
    b.resize(n);
    fft(a, false);
    fft(b, false);
    for (ll i = 0; i < n; i++) {
        a[i] *= b[i];
    }
    fft(a, true);
    vector<ll> ret;
    for (auto i: a) ret.push_back((ll) round(i.real()));
	while (ret.back() == 0) ret.pop_back();
    return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	ll N, M; cin >> N >> M;
	vector<ll> A(N + 1), B(M + 1);
	for (ll i = 0; i < N + 1; ++i) cin >> A[i];
	for (ll i = 0; i < M + 1; ++i) cin >> B[i];
	auto ret = multiply(A, B);
	// for (auto i: ret) cout << i << ' ';
	ll ans = 0;
	for (auto i: ret) ans ^= i;
	cout << ans;
}
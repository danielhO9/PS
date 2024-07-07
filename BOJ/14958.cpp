#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef complex<double> base;

void fft(vector<base>& a, bool inv) {
    ll n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while (!((j ^= bit) & bit)) bit >>= 1;
        if (i < j) swap(a[i], a[j]);
    }
    for (int i = 1; i < n; i <<= 1) {
        double x = inv ? M_PI / i : -M_PI / i;
        base w = {cos(x), sin(x)};
        for (int j = 0; j < n; j += i << 1) {
            base th = {1, 0};
            for (int k = 0; k < i; k++) {
                base tmp = a[i + j + k] * th;
                a[i + j + k] = a[j + k] - tmp;
                a[j + k] += tmp;
                th *= w;
            }
        }
    }
    if (inv) {
        for (int i = 0; i < n; i++) a[i] /= n;
    }
}

vector<ll> multiply(vector<ll>& A, vector<ll>& B) {
    vector<base> a(A.begin(), A.end()), b(B.begin(), B.end());
    ll n = max(a.size(), b.size());
    ll i = 0;
    while ((1 << i) < (n << 1)) i++;
    n = 1 << i;
    a.resize(n);
    b.resize(n);
    fft(a, false);
    fft(b, false);
    for (ll i = 0; i < n; i++) a[i] *= b[i];
    fft(a, true);
    vector<ll> ret;
    for (auto i: a) ret.push_back((ll) round(i.real()));
	while (ret.back() == 0) ret.pop_back();
    return ret;
}

void solve() {
	int n, m; cin >> n >> m;
	string R, Y; cin >> R >> Y;
	vector<ll> r1(n), r2(n), r3(n);
	vector<ll> y1(m), y2(m), y3(m);
	for (int i = 0; i < n; ++i) {
		if (R[i] == 'R') r1[i] = 1ll;
		else if (R[i] == 'P') r2[i] = 1ll;
		else r3[i] = 1;
	}
	for (int i = 0; i < m; ++i) {
		if (Y[i] == 'P') y1[i] = 1ll;
		else if (Y[i] == 'S') y2[i] = 1ll;
		else y3[i] = 1ll;
	}
	// reverse(y1.begin(), y1.end());
	// reverse(y2.begin(), y2.end());
	// reverse(y3.begin(), y3.end());
	multiply(r1, y1);
	// for (int i = 0; i < 3; ++i) {
	// 	res[i] = multiply(r[i], y[i]);
	// }
	ll ans = 0;
	// for (int i = m - 1; i < n + m - 1; ++i) {
	// 	ans = max(ans, res[0][i] + res[1][i] + res[2][i]);
	// }
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}
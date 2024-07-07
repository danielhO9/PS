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
    for (ll i = 0; i < n; i++) {
        a[i] *= b[i];
    }
    fft(a, true);
    vector<ll> ret;
    for (auto i: a) ret.push_back((ll) round(i.real()));
	while (ret.back() == 0) ret.pop_back();
    return ret;
}

void solve() {
	vector<ll> arr(500000);
	for (int i = 1; i <= 5e5; ++i) {
		for (int j = i; j <= 5e5; j += i) ++arr[j];
	}
	vector<ll> mul = multiply(arr, arr);
	int n; cin >> n;
	for (int i = 0; i < n; ++i) {
		int idx = 0; ll val = 0;
		int a, b; cin >> a >> b;
		for (int j = a; j <= b; ++j) {
			if (val < mul[j]) {
				idx = j; val = mul[j];
			}
		}
		cout << idx << ' ' << val << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}
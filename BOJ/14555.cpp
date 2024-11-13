#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void fwht_xor(vector<ll> &a, bool inv) {
    ll n = a.size();
    for(ll s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
        for(ll l = 0; l < n; l += s) {
            for(ll i = 0; i < h; i++) {
                ll t = a[l + h + i];
                a[l + h + i] = a[l + i] - t;
                a[l + i] += t;
                if(inv) a[l + h + i] /= 2, a[l + i] /= 2;
            }
        }
    }
}

ll N, M;

void solve() {
	cin >> N >> M;
	vector<ll> a(M + 1);
	for (int i = 0; i < N; ++i) {
		ll tmp; cin >> tmp;
		tmp %= (M + 1); ++a[tmp];
	}
	ll n = M + 1;
    ll i = 0;
    while ((1 << i) < n) i++;
    n = 1 << i;
    a.resize(n);
	vector<ll> b(a.begin(), a.end());
	fwht_xor(b, false);
	for (int i = 0; i < n; ++i) b[i] = b[i] * b[i] * b[i];
	fwht_xor(b, true);
	for (int i = 0; i < n; ++i) b[i] -= a[i] * (3*N-2);
	cout << b[0] / 6;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}
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

ll n;

void solve() {
	cin >> n;
	vector<ll> a(n + 1);
	for (ll i = 1; i <= n; ++i) cin >> a[i];
	for (ll i = 1; i <= n; ++i) a[i] ^= a[i - 1];
	vector<ll> b(1 << 16, 0);
	for (ll i = 0; i <= n; ++i) ++b[a[i]];
	// for (ll i = 0; i < 4; ++i) cout << b[i] << ' ';
	// cout << '\n';
	fwht_xor(b, false);
	for (ll i = 0; i < (1 << 16); ++i) b[i] *= b[i];
	fwht_xor(b, true);
	// for (ll i = 0; i < 10; ++i) cout << b[i] << ' ';
	// cout << '\n';
	b[0] -= n + 1;
	ll val = 0, cnt = 0;
	for (ll i = 0; i < (1 << 16); ++i) {
		if (b[i] > cnt) {
			val = i;
			cnt = b[i];
		}
	}
	cout << val << ' ' << cnt / 2;
	
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}
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

vector<ll> convolute(vector<ll>& A, vector<ll>& B) {
    vector<ll> a(A.begin(), A.end()), b(B.begin(), B.end());
    ll n = max(a.size(), b.size());
    ll i = 0;
    while ((1 << i) < (n << 1)) i++;
    n = 1 << i;
    a.resize(n);
    b.resize(n);
    fwht_xor(a, false);
    fwht_xor(b, false);
    for (ll i = 0; i < n; i++) {
        a[i] *= b[i];
    }
    fwht_xor(a, true);
    return a;
}

int H, W;

void solve() {
	cin >> H >> W;
	vector<ll> f(1 << W), g(1 << W);
	for (int i = 0; i < H; ++i) {
		string s; cin >> s;
		int val = 0;
		for (int j = 0; j < W; ++j) if (s[j] == '1') val += (1 << j);
		++f[val];
	}
	for (int i = 0; i < (1 << W); ++i) {
		int cnt = __builtin_popcount(i);
		g[i] = min(cnt, W - cnt);
	}
	auto conv = convolute(f, g);
	ll ans = INT32_MAX;
	for (int i = 0; i < (1 << W); ++i) ans = min(ans, conv[i]);
	cout << ans;
	
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}
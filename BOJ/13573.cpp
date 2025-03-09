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
int arr[20][100000];

void solve() {
	cin >> H >> W;
	vector<ll> f(1 << H), g(1 << H);
	for (int i = 0; i < H; ++i) {
		string s; cin >> s;
		for (int j = 0; j < W; ++j) arr[i][j] = (s[j] == 'T');
	}
	for (int i = 0; i < W; ++i) {
		int val = 0;
		for (int j = 0; j < H; ++j) if (arr[j][i]) val ^= (1 << j);
		++f[val];
	}
	for (int i = 0; i < (1 << H); ++i) {
		int cnt = __builtin_popcount(i);
		g[i] = min(cnt, H - cnt);
	}
	auto conv = convolute(f, g);
	ll ans = INT32_MAX;
	for (int i = 0; i < (1 << H); ++i) ans = min(ans, conv[i]);
	cout << ans;
	
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}

/*
10 5
10000
00111
11000
01000
10110
01110
10101
00100
00100
10001

5 10
1010101001
0011010000
0100111110
0100110000
0100001001

0 1 1 1 2 0 0 0 0 0 0 0 0 1 1 0 0 1 0 0 0 1 0 0 0 0 0 0 1 0 0 0
*/
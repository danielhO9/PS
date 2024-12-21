#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m, K;
ll a[200][200];
vector<vector<ll>> moved(200, vector<ll>(200));

void solve() {
	cin >> n >> m >> K;
	for (ll i = 0; i < n; ++i) for (ll j = 0; j < m; ++j) cin >> a[i][j];

	for (ll i = 0; i < m; ++i) {
		for (ll j = 0; j < m; ++j) {
			moved[i][j] = a[0][(j + i) % m];
		}
	}
	for (ll i = 0; i < m; ++i) {
		for (ll j = 1; j < m; ++j) moved[i][j] += moved[i][j - 1];
		for (ll j = 0; j < m; ++j) moved[i][j] += K * i;
	}
	// for (ll i = 0; i < m; ++i) {
	// 	for (ll j = 0; j < m; ++j) cout << moved[i][j] << ' ';
	// 	cout << '\n';
	// }

	for (ll i = 1; i < n; ++i) {
		vector<ll> tmp(m, LLONG_MAX);
		for (ll j = 0; j < m; ++j) for (ll k = 0; k < m; ++k) {
			tmp[k] = min(tmp[k], moved[j][k]);
		}
		for (ll k = 0; k < m; ++k) {
			for (ll j = 0; j < m; ++j) {
				moved[k][j] = tmp[j] + a[i][(j + k) % m];
			}
			for (ll j = 1; j < m; ++j) {
				moved[k][j] = min(moved[k][j], moved[k][j - 1] + a[i][(j + k) % m]);
			}
			for (ll j = 0; j < m; ++j) {
				moved[k][j] += K * k;
			}
		}
	}
	vector<ll> tmp(m, LLONG_MAX);
	for (ll j = 0; j < m; ++j) for (ll k = 0; k < m; ++k) {
		tmp[k] = min(tmp[k], moved[j][k]);
	}
	cout << tmp[m - 1] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	ll t; cin >> t;
	while (t--) solve();
}
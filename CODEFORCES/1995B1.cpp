#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m;
ll a[200000];

void solve() {
	cin >> n >> m;
	map<ll, ll> M;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		++M[a[i]];
	}
	vector<pair<ll, ll>> v;
	for (auto [i, j]: M) {
		v.push_back({i, j});
	}
	// for (auto [i, j]: v) cout << i << ' ' << j << '\n';
	// cout << '\n';
	ll ans = 0ll;
	int cnt = 0;
	for (int i = 0; i < v.size(); ++i) {
		ans = max(ans, min(m / v[i].first, v[i].second) * v[i].first);
		if (i + 1 < v.size() && v[i].first + 1 == v[i + 1].first) {
			ll maxv = v[i].first * v[i].second + v[i + 1].first * v[i + 1].second;
			if (maxv <= m) {
				ans = max(ans, maxv);
				continue;
			}
			for (int j = 1; j <= v[i].second; ++j) {
				++cnt;
				ll tmp = j * v[i].first;
				if (tmp > m) break;
				ans = max(ans, tmp + min((m - tmp) / v[i + 1].first, v[i + 1].second) * v[i + 1].first);
				if (ans == m) {
					cout << ans << '\n';
					return;
				}
			}
		}
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}
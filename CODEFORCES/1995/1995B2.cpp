#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m;
ll a[200000];
ll c[200000];

void solve() {
	cin >> n >> m;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) cin >> c[i];
	vector<pair<ll, ll>> v;
	for (int i = 0; i < n; ++i) {
		v.push_back({a[i], c[i]});
	}
	sort(v.begin(), v.end());

	// for (auto [i, j]: v) cout << i << ' ' << j << '\n';
	// cout << '\n';

	ll ans = 0ll;
	for (int i = 0; i < v.size(); ++i) {
		// cout << i << "\n";

		if (ans == m) {
			cout << ans << '\n';
			return;
		}

		ans = max(ans, min(m / v[i].first, v[i].second) * v[i].first);
		
		if (i + 1 < v.size() && v[i].first + 1 == v[i + 1].first) {
			
			ll x = v[i].first;
			ll maxv = x * v[i].second + (x + 1) * v[i + 1].second;
			if (maxv <= m) {
				ans = max(ans, maxv);
				continue;
			}
			
			ll now = min(m / x, v[i].second);
			ll val = now * x;
			ll nxt = (m - val) / (x + 1);
			val += nxt * (x + 1);
			ll rem = m - val;
			rem = max(0ll, rem - min(now, v[i + 1].second - nxt));
			ans = max(ans, m - rem);

			now = min(m / (x + 1), v[i + 1].second);
			val = now * (x + 1);
			nxt = (m - val) / x;
			val += nxt * x;
			if (val == m) {
				cout << m << '\n';
				return;
			}
			val += x;
			++nxt;
			rem = val - m;
			if (rem <= min(now, v[i].second - nxt)) {
				cout << m << '\n';
				return;
			}


		}
		// cout << i << ' ' << ans << '\n';
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;
ll a[500000], b[500000];

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i] >> b[i];
	ll suma = 0, sumb = 0;
	for (int i = 0; i < n; ++i) {
		suma += a[i];
		sumb += b[i];
	}
	vector<bool> avail(n, false);
	bool flag = false;
	for (int i = 0; i < n; ++i) {
		if (suma <= sumb - b[i]) {
			avail[i] = true;
			flag = true;
		}
	}
	if (!flag) {
		cout << -1 << '\n';
		return;
	}
	vector<ll> cost(n);
	for (int i = 0; i < n; ++i) {
		cost[i] = a[i] + b[i];
		cost[i] = -1ll * min(cost[i], suma);
	}
	int idx = -1; ll val = LLONG_MIN;
	for (int i = 0; i < n; ++i) if (avail[i]) {
		if (val < cost[i]) {
			val = cost[i];
			idx = i;
		}
	}
	priority_queue<pair<ll, ll>> pq;

	for (int i = 0; i < n; ++i) if (i != idx) {
		pq.push(make_pair(-cost[i], i));
	}
	ll x = 0;
	ll ans = suma;
	// cout << ans << '\n';
	while (!pq.empty()) {
		int cur = pq.top().second; pq.pop();
		// cout << a[cur] << ' ' << b[cur] << ' ' << x << '\n';
		if (a[cur] <= x) {
			x = x - a[cur] + b[cur];
		} else {
			ans += a[cur] - x;
			x = b[cur];
		}
		// cout << ans << '\n';
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}
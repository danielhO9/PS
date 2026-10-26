#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll cache[1000000];

void solve() {
	int n, m; cin >> n >> m;
	vector<ll> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
	vector<ll> b(n); for (int i = 0; i < n; ++i) cin >> b[i];
	vector<ll> d(n); for (int i = 0; i < n; ++i) d[i] = a[i] - b[i];
	vector<ll> c(m); for (int i = 0; i < m; ++i) cin >> c[i];

	vector<pair<ll, ll>> arr;
	for (int i = 0; i < n; ++i) arr.push_back({d[i], a[i]});
	sort(arr.begin(), arr.end());

	vector<pair<ll, ll>> fin;
	for (int i = 0; i < n; ++i) {
		if (fin.empty()) fin.push_back(arr[i]);
		else if (fin.back().second > arr[i].second) fin.push_back(arr[i]);
	}
	// for (auto i: fin) {
	// 	cout << i.first << ' ' << i.second << '\n';
	// }
	for (int i = 0; i < 1e6; ++i) {
		ll rem = i;
		ll tans = 0;
		ll tmp = (rem - fin[0].second + fin[0].first) / fin[0].first;
		if (tmp > 0) {
			tans += 2 * tmp;
			rem -= tmp * fin[0].first;
			cache[i] = cache[rem] + tans;
			continue;
		}
		if (rem < fin.back().second) continue;
		int l = 0, r = (int)fin.size() - 1;
		while (l + 1 < r) {
			int mid = (l + r) / 2;
			if (fin[mid].second > rem) l = mid;
			else r = mid;
		}
		int idx = r;
		tmp = (rem - fin[idx].second + fin[idx].first) / fin[idx].first;
		if (tmp < 0) break;
		tans += 2 * tmp;
		rem -= tmp * fin[idx].first;
		cache[i] = cache[rem] + tans;
	}

	ll ans = 0; int idx = 0;
	for (int i = 0; i < m; ++i) {
		idx = 0;
		ll rem = c[i];
		ll tmp = (rem - fin[idx].second + fin[idx].first) / fin[idx].first;
		if (tmp > 0) {
			ans += 2 * tmp;
			rem -= tmp * fin[idx].first;
		}
		if (rem < 1e6) {
			ans += cache[rem];
			continue;
		}
		while (true) {
			if (rem < fin.back().second) break;
			int l = idx, r = (int)fin.size() - 1;
			while (l + 1 < r) {
				int mid = (l + r) / 2;
				if (fin[mid].second > rem) l = mid;
				else r = mid;
			}
			idx = r;
			ll tmp = (rem - fin[idx].second + fin[idx].first) / fin[idx].first;
			if (tmp < 0) break;
			ans += 2 * tmp;
			rem -= tmp * fin[idx].first;
			if (rem < 1e6) {
				ans += cache[rem];
				break;
			}
		}
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}
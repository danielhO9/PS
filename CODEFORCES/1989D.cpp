#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
	ll ans = 0; int idx = 0;
	for (int i = 0; i < m; ++i) {
		idx = 0;
		ll rem = c[i];
		while (true) {
			ll tmp = (rem - fin[idx].second) / fin[i].first;
			ans += 2 * tmp;
			rem -= tmp * fin[idx].first;
			if (rem < fin.back().second) break;
			int l = 0, r = (int)fin.size() - 1;
			while (l + 1 < r) {
				int mid = (l + r) / 2;
				if (fin[mid].second > rem)  
			}
		}
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}
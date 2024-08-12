#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, k;
ll a[200000];
ll b[200000];
vector<pair<ll, ll>> v;

bool possible(vector<ll>& arr1, vector<ll>& arr2, ll x) {
	ll tar = (n - 2) / 2;
	ll cnt = 0;
	for (auto i: arr2) if (i < x) ++cnt;
	if (cnt > tar) return false;
	tar -= cnt;
	ll sum = 0;
	for (int i = tar; i < arr1.size(); ++i) {
		if (arr1[i] < x) sum += x - arr1[i];
	}
	return sum <= k;
}

void solve() {
	cin >> n >> k;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) cin >> b[i];
	v.clear();

	for (int i = 0; i < n; ++i) v.push_back({a[i], i});
	sort(v.begin(), v.end());

	ll medi = (n - 1) / 2;
	vector<ll> med(n);

	for (int i = 0; i < medi; ++i) {
		if (n % 2) med[i] = medi;
		else med[i] = medi + 1;
	}
	for (int i = medi + 1; i < n; ++i) {
		if (n % 2) med[i] = medi - 1;
		else med[i] = medi;
	}
	if (n % 2) med[medi] = medi - 1;
	else med[medi] = medi + 1;

	ll ans = 0ll;
	for (int i = 0; i < n; ++i) {
		if (b[v[i].second]) {
			ans = max(ans, v[i].first + v[med[i]].first + k);
		}
	}

	// ll maxa = 0ll;
	// for (int i = 0; i < medi; ++i) {
	// 	if (!b[v[i].second]) maxa = max(maxa, v[i].first);
	// }
	// if (n % 2 == 0 && !b[v[medi].second]) maxa = max(maxa, v[medi].first);
	// if (maxa != 0ll) {
	// 	ll maxv = LLONG_MAX;
	// 	vector<ll> tmp;
	// 	for (int i = med[0]; i < n; ++i) {
	// 		if (b[v[i].second]) tmp.push_back(v[i].first);
	// 		else maxv = min(maxv, v[i].first);
	// 	}
	// 	if (!tmp.empty()) {
	// 		ll l = tmp[0], r = min(maxv + 1, tmp[0] + k + 1);
	// 		while (l + 1 < r) {
	// 			ll mid = (l + r) / 2;
	// 			if (possible(tmp, mid)) l = mid;
	// 			else r = mid;
	// 		}
	// 		ans = max(ans, maxa + l);
	// 	} else {
	// 		ans = max(ans, maxv + maxa);
	// 	}
	// }

	ll maxa = 0ll;
	ll maxidx = 0ll;
	for (int i = n%2 ? medi : medi + 1; i < n; ++i) {
		if (!b[v[i].second] && maxa < v[i].first) {
			maxa = max(maxa, v[i].first);
			maxidx = i;
		}
	}
	// cout << maxa << ' ';
	if (maxa != 0ll) {
		vector<ll> change, nchange;
		for (int i = 0; i < n; ++i) if (i != maxidx) {
			if (b[v[i].second]) change.push_back(v[i].first);
			else nchange.push_back(v[i].first);
		}
		// for (auto i: change) cout << i  << ' ';
		// cout << '\n';
		// for (auto i: nchange) cout << i  << ' ';
		// cout << '\n';
		ll l = 0ll, r = v[n - 1].first + k + 1;
		while (l + 1 < r) {
			ll mid = (l + r) / 2;
			// cout << l << ' ' << r  << '\n';
			if (possible(change, nchange, mid)) {
				// cout << mid << ' ';
				l = mid;
			}
			else r = mid;
		}
		ans = max(ans, maxa + l);
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}
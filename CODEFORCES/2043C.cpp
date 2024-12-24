#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;
ll a[200000];

pair<ll, ll> subprob(ll l, ll r) {
	vector<ll> tmp;
	for (int i = l; i <= r; ++i) tmp.push_back(a[i]);
	ll mx = 0, mn = 0;
	ll tmx = 0, tmn = 0;
	ll sum = 0ll;
	for (int i = 0; i < tmp.size(); ++i) {
		sum += tmp[i];
		mx = max(mx, sum - tmn);
		mn = min(mn, sum - tmx);
		tmx = max(tmx, sum);
		tmn = min(tmn, sum);
	}
	return make_pair(mn, mx);
}

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	ll xidx = -1;
	for (int i = 0; i < n; ++i) if (a[i] != 1 && a[i] != -1) xidx = i;
	set<ll> ans;
	if (xidx != -1) {
		ll rmx = 0, rmn = 0, lmx = 0, lmn = 0;
		if (xidx > 0) {
			auto tmp = subprob(0, xidx - 1);
			for (ll i = tmp.first; i <= tmp.second; ++i) ans.insert(i);
			ll sum = 0ll;
			for (int i = xidx - 1; i >= 0; --i) {
				sum += a[i];
				lmx = max(lmx, sum);
				lmn = min(lmn, sum);
			}
		}
		if (xidx < n - 1) {
			auto tmp = subprob(xidx + 1, n - 1);
			for (ll i = tmp.first; i <= tmp.second; ++i) ans.insert(i);
			ll sum = 0ll;
			for (int i = xidx + 1; i < n; ++i) {
				sum += a[i];
				rmx = max(rmx, sum);
				rmn = min(rmn, sum);
			}
		}
		for (ll i = lmn + rmn + a[xidx]; i <= rmx+lmx+a[xidx]; ++i) ans.insert(i);
	} else {
		auto tmp = subprob(0, n - 1);
		for (ll i = tmp.first; i <= tmp.second; ++i) ans.insert(i);
	}
	ans.insert(0);
	cout << ans.size() << '\n';
	for (auto i: ans) cout << i << ' ';
	cout << '\n';

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}
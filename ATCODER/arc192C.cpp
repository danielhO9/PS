#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll query(ll s, ll t) {
	cout << "? " << s << ' ' << t << '\n';
	cout.flush();
	ll ret; cin >> ret;
	return ret;
}

ll N;

void solve() {
	cin >> N;
	vector<pair<ll, ll>> l, r;
	ll th = query(1, 2);
	r.push_back({th, 2});
	for (ll i = 3; i <= N; ++i) {
		ll v1 = query(1, i);
		ll v2 = query(2, i);
		if (v1 < th && v2 < th) r.push_back({v1, i});
		else if (v2 < v1) r.push_back({v1, i});
		else l.push_back({-v1, i});
	}
	sort(l.begin(), l.end());
	sort(r.begin(), r.end());
	vector<ll> P;
	P.push_back(0);
	for (auto i: l) P.push_back(i.second);
	P.push_back(1);
	for (auto i: r) P.push_back(i.second);
	vector<ll> ans(N + 1);
	vector<ll> val;
	for (ll i = 0; i <= N; ++i) ans[P[i]] = i;

	ll sm = query(P[1], P[N]);
	ll lsm = 0, rsm = 0;
	if (!r.empty()) lsm = sm - query(1, r.back().second);
	else lsm = query(l.front().second, l.back().second);
	if (!l.empty()) rsm = sm - query(l.front().second, 1);
	else rsm = query(r.front().second, r.back().second);
	ll v1 = sm - lsm - rsm;
	for (ll i = 0; i + 1 < l.size(); ++i) val.push_back(l[i + 1].first - l[i].first);
	if (!l.empty()) val.push_back(-l.back().first - v1);
	val.push_back(v1);
	if (!r.empty()) val.push_back(r.front().first - v1);
	for (ll i = 1; i < r.size(); ++i) val.push_back(r[i].first - r[i - 1].first);
	cout << "! ";
	for (ll i = 1; i <= N; ++i) cout << ans[i] << ' ';
	for (auto i: val) cout << i << ' ';
	cout << '\n';
	cout.flush();
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}
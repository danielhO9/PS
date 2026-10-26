#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;

ll n, m;
vector<pair<ll, ll>> v;
ll fac[400001], ifac[4000001];

ll pow(ll a, ll b) {
	if (b == 0) return 1ll;
	ll half = pow(a, b / 2);
	half = (half * half) % MOD;
	if (b % 2) return (half * a) % MOD;
	else return half;
}

void init() {
	ll val = 1;
	fac[0] = 1;
	ifac[0] = 1;
	for (int i = 1; i <= 4e5; ++i) {
		val *= i; val %= MOD;
		fac[i] = val;
		ifac[i] = pow(fac[i], MOD - 2);
	}
}

ll comb(ll a, ll b) {
	ll ret = fac[a];
	ret *= ifac[b]; ret %= MOD;
	ret *= ifac[a - b]; ret %= MOD;
	return ret;
}

// Cx = 2xCx - 2xCx-1
ll catalan(ll x) {
	if (x == 0) return 1ll;
	ll ret = comb(2 * x, x);
	ret -= comb(2 * x, x - 1);
	ret += MOD;
	ret %= MOD;
	return ret;
}

ll calc(ll l, ll r) {
	if (l == r) return catalan(v[l].second - v[l].first);
	ll len = v[l].second - v[l].first;
	// cout << "cur: " << v[l].first << ' ' << v[l].second << '\n';

	ll val = v[l].first;
	ll s = l + 1;
	vector<ll> child;

	while (true) {
		auto itr = lower_bound(v.begin() + s, v.begin() + r + 1, make_pair(val, 0), [](const pair<ll, ll>& a, const pair<ll, ll>& b) {
			return a.first < b.first;
		});
		if (itr == v.begin() + r + 1) break;
		ll idx = itr - v.begin();
		child.push_back(idx);
		len -= v[idx].second - v[idx].first;
		val = v[idx].second;
		s = idx + 1;
		if (s >= r + 1) break;
	}

	ll ret = catalan(len);

	child.push_back(r + 1);
	for (int i = 0; i + 1 < child.size(); ++i) {
		ret *= calc(child[i], child[i + 1] - 1);
		ret %= MOD;
	}

	return ret;
}

void solve() {
	cin >> n >> m;
	v.clear();
	bool flag = false;
	for (int i = 0; i < m; ++i) {
		ll l, r; cin >> l >> r;
		if (l != r) {
			v.push_back({l, r});
			if (l == 1 && r == n) flag = true;
		}
	}
	if (!flag) v.push_back({1, n});
	sort(v.begin(), v.end(), [] (const pair<ll, ll>& a, const pair<ll, ll>& b) {
		if (a.first == b.first) return a.second > b.second;
		return a.first < b.first;
	});
	cout << calc(0, (int)v.size() - 1) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	init();
	int t; cin >> t;
	while (t--) solve();
}
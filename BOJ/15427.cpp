#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;

void solve() {
	cin >> n;
	vector<pair<ll, ll>> pts;
	unordered_map<ll, unordered_map<ll, bool>> m;
	for (int i = 0; i < n; ++i) {
		ll x, y; cin >> x >> y;
		m[x][y] = true;
		pts.push_back({x, y});
	}
	ll ans = 0;
	vector<pair<ll, ll>> dif = {
		{0, 2018},
		{0, -2018},
		{2018, 0},
		{-2018, 0},
		{1118, 1680},
		{1118, -1680},
		{-1118, 1680},
		{-1118, -1680},
		{1680, 1118},
		{-1680, 1118},
		{1680, -1118},
		{-1680, -1118},
	};
	for (auto i: pts) {
		for (auto j: dif) {
			if (m.find(i.first + j.first) != m.end() && m[i.first + j.first].find(i.second + j.second) != m[i.first + j.first].end()) {
				++ans;
			}
		}
	}
	cout << ans / 2;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}
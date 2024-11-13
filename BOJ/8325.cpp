#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;
ll t[2000];
ll cache[2000][2000];
vector<pair<ll, ll>> l[2000], r[2000];

void solve() {
	cin >> n;
	for (ll i = 0; i < n; ++i) cin >> t[i];
	for (ll i = 0; i < n; ++i) for (ll j = 0; j < n; ++j) cache[i][j] = INT32_MAX;

	for (ll i = 0; i < n; ++i) cache[i][i] = t[i];
	for (ll i = 0; i < n; ++i) {
		l[i].push_back({t[i], i});
		if (i - 1 >= 0) l[i].push_back({t[i] + t[i - 1], i - 1});
		r[i].push_back({t[i], i});
		if (i + 1 < n) r[i].push_back({t[i] + t[i + 1], i + 1});
	}

	for (ll dif = 1; dif < n; ++dif) {
		for (ll s = 0; s + dif < n; ++s) {
			// s, s + dif
			for (auto& [_, i]: l[s + dif]) {
				cache[s][s + dif] = min(cache[s][s + dif], max((i - 1 >= s ? cache[s][i - 1] : 0) + t[i], (i + 1 <= s + dif ? cache[i + 1][s + dif] : 0) + t[i]));
			}
			for (auto& [_, i]: r[s]) {
				cache[s][s + dif] = min(cache[s][s + dif], max((i - 1 >= s ? cache[s][i - 1] : 0) + t[i], (i + 1 <= s + dif ? cache[i + 1][s + dif] : 0) + t[i]));
			}
			if (s + dif + 1 < n) {
				ll val = cache[s][s + dif] + t[s + dif + 1];
				while (!r[s].empty() && r[s].back().first >= val) r[s].pop_back();
				r[s].push_back({val, s + dif + 1});
			}

			if (s - 1 >= 0) {
				ll val = cache[s][s + dif] + t[s - 1];
				while (!l[s + dif].empty() && l[s + dif].back().first >= val) l[s + dif].pop_back();
				l[s + dif].push_back({val, s - 1});
			}
		}
	}
	cout << cache[0][n - 1];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}
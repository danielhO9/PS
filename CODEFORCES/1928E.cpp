#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL cache[200001];
LL last[200001];
vector<LL> ans;

void init() {
	memset(cache, -1, sizeof(cache));
	cache[0] = 0;
	for (LL i = 1; i <= 10000; ++i) {
		if ((i * (i + 1) / 2) > 200000) break;
		cache[i * (i + 1) / 2] = i + 1;
		last[i * (i + 1) / 2] = i + 1;
	}
	vector<pair<int, int>> v;
	for (LL i = 0; i <= 200000; ++i) {
		if (cache[i] != -1) {
			v.push_back({i, cache[i]});
		} else {
			cache[i] = 987654321;
			for (auto j: v) {
				if (cache[i] > j.second + cache[i - j.first]) {
					cache[i] = j.second + cache[i - j.first];
					last[i] = j.second;
				}
			}
		}
	}
	// for (LL i = 0; i < 6; ++i) cout << cache[i] << ' '; cout << '\n';
	// for (LL i = 0; i < 6; ++i) cout << last[i] << ' '; cout << '\n';
}

void solve() {
	ans.clear();
	LL n, x, y, s; cin >> n >> x >> y >> s;
	LL mod = x % y;
	s -= (x % y) * n; x /= y;
	if (s < x) { cout << "NO\n"; return; }
	if (s % y != 0) { cout << "NO\n"; return; }
	s /= y;
	LL tx = x, tsum = x, tn = n - 1;
	bool avail = false;
	while (true) {
		// cout << s - tsum << ' ' << cache[s - tsum] << ' ' << tn << '\n';
		if (tsum > s || n <= 0) break;
		if (cache[s - tsum] <= tn) {
			avail = true;
			for (LL i = x; i <= tx; ++i) ans.push_back(i);
			break;
		}
		++tx; tsum += tx; --tn;
	}
	if (!avail) { cout << "NO\n"; return; }
	else cout << "YES\n";
	LL t = s - tsum;
	while (true) {
		if (t <= 0) break;
		for (LL i = 0; i < last[t]; ++i) ans.push_back(i);
		t -= last[t] * (last[t] - 1) / 2;
	}
	while (ans.size() < n) ans.push_back(0);
	for (auto i: ans) cout << i * y + mod << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	int t; cin >> t;
	while (t--) solve();
}
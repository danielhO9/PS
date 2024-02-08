#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	int n; cin >> n;
	int a[n]; for (int i = 0; i < n; ++i) cin >> a[i];
	map<int, int> first, last;
	for (int i = 0; i < n; ++i) {
		last[a[i]] = i;
		if (first.find(a[i]) == first.end()) first[a[i]] = i;
	}
	vector<int> start, end;
	for (auto [i, j]: first) start.push_back(j);
	for (auto [i, j]: last) end.push_back(j);
	// for (auto i: start) cout << i << ' ';
	// cout << '\n';
	// for (auto i: end) cout << i << ' ';
	// cout << '\n';
	sort(start.begin(), start.end());
	sort(end.begin(), end.end());
	LL ans = 0; int stid = 0, edid = 0;
	while (stid < start.size()) {
		while (edid < end.size() && start[stid] > end[edid]) {
			++edid;
			if (edid == end.size()) break;
		}
		ans += (LL) end.size() - edid;
		++stid;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while (t--) solve();
}

/*
1
4
2 3 2 1
*/
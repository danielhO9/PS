#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	int minx = 1, maxx = 1e9; set<int> none;
	while (n--) {
		int a, x; cin >> a >> x;
		if (a == 1) {
			minx = max(minx, x);
			while (!none.empty() && *none.begin() < minx) none.erase(none.begin());
		} else if (a == 2) {
			maxx = min(maxx, x);
			while (!none.empty() && *prev(none.end()) > maxx) none.erase(prev(none.end()));
		} else {
			if (minx <= x && x <= maxx) none.insert(x);
		}
	}
	if (minx > maxx) cout << 0 << '\n';
	else cout << maxx - minx + 1 - (int) none.size() << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}
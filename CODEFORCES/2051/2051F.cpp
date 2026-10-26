#include <bits/stdc++.h>
using namespace std;

int n, m, q;

void solve() {
	cin >> n >> m >> q;
	deque<pair<int, int>> seg;
	seg.push_back({m, m});
	for (int i = 0; i < q; ++i) {
		int a; cin >> a;
		if (i == 0 && a == m) {
			seg.pop_back();
			seg.push_back({1, 1});
			seg.push_back({n, n});
			cout << 2 << ' ';
			continue;
		}

		bool flag = false;
		for (auto& j: seg) {
			if (!(j.first <= a && a <= j.second)) {
				if (a < j.first) --j.first;
				if (j.second < a) ++j.second;
			} else flag = true;
		}
		if (flag) {
			if (seg.front().first != 1) seg.push_front({1, 1});
			if (seg.back().second != n) seg.push_back({n, n});
		}
		if (seg.size() == 3) {
			if (seg[2].first <= seg[1].second) {
				pair<int, int> tmp = {seg[1].first, seg[2].second};
				seg.pop_back();
				seg.pop_back();
				seg.push_back(tmp);
			}
		}
		if (seg.size() >= 2) {
			if (seg[1].first <= seg[0].second) {
				pair<int, int> tmp = {seg[0].first, seg[1].second};
				seg.pop_front();
				seg.pop_front();
				seg.push_front(tmp);
			}
		}
		int ans = 0;
		for (auto& j: seg) ans += j.second - j.first + 1;
		cout << ans << ' ';
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}
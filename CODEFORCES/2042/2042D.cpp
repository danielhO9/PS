#include <bits/stdc++.h>
using namespace std;

struct Interval {
	int l, r, idx;
};

int n;
vector<Interval> ints;

void solve() {
	ints.clear();
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int l, r; cin >> l >> r;
		ints.push_back({l, r, i});
	}
	sort(ints.begin(), ints.end(), [](const Interval& a, const Interval& b) {
		if (a.l == b.l) return a.r > b.r;
		return a.l < b.l;
	});
	vector<int> ans(n, 0);
	set<int> r;
	for (int i = 0; i < n; ++i) {
		if (!r.empty()) {
			auto itr = r.lower_bound(ints[i].r);
			if (itr != r.end()) ans[ints[i].idx] += *itr - ints[i].r;
		}
		r.insert(ints[i].r);
	}
	// for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
	// cout << '\n';

	set<int> l;
	sort(ints.begin(), ints.end(), [](const Interval& a, const Interval& b) {
		if (a.r == b.r) return a.l < b.l;
		return a.r > b.r;
	});
	for (int i = 0; i < n; ++i) {
		if (!l.empty()) {
			auto itr = l.upper_bound(ints[i].l);
			if (itr != l.begin()) ans[ints[i].idx] += ints[i].l - *prev(itr);
		}
		l.insert(ints[i].l);
	}
	for (int i = 0; i < n - 1; ++i) {
		if (ints[i].l == ints[i + 1].l && ints[i].r == ints[i + 1].r) {
			ans[ints[i].idx] = 0;
			ans[ints[i + 1].idx] = 0;
		}
	}
	for (int i = 0; i < n; ++i) cout << ans[i] << '\n';
	// cout << '\n';

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}
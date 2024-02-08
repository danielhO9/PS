#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	int a[n], d[n];
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) cin >> d[i];
	vector<int> l(n), r(n);
	for (int i = 0; i < n; ++i) {
		if (i == 0) l[i] = i;
		else l[i] = i - 1;
		if (i == n - 1) r[i] = i;
		else r[i] = i + 1;
	}
	vector<int> receive(n);
	for (int i = 0; i < n; ++i) {
		if (i != l[i]) receive[l[i]] += a[i];
		if (i != r[i]) receive[r[i]] += a[i];
	}
	vector<int> c;
	vector<bool> inA(n, true);
	for (int i = 0; i < n; ++i) if (receive[i] > d[i]) {
		c.push_back(i);
		inA[i] = false;
	}
	vector<int> ans;
	while (true) {
		ans.push_back(c.size());
		if (ans.size() == n || c.size() == 0) break;
		set<int> t;
		for (auto i: c) {
			if (l[i] != i) {
				if (inA[l[i]]) t.insert(l[i]);
				receive[l[i]] -= a[i];
				if (r[i] != i) {
					receive[l[i]] += a[r[i]];
					r[l[i]] = r[i];
				} else {
					r[l[i]] = l[i];
				}
			}
			if (r[i] != i) {
				if (inA[r[i]]) t.insert(r[i]);
				receive[r[i]] -= a[i];
				if (l[i] != i) {
					receive[r[i]] += a[l[i]];
					l[r[i]] = l[i];
				} else {
					l[r[i]] = r[i];
				}
			}
		}
		c.clear();
		for (auto i: t) if (receive[i] > d[i]) {
			c.push_back(i);
			inA[i] = false;
		}
	}
	while (ans.size() < n) ans.push_back(0);
	for (auto i: ans) cout << i << ' ';
	cout << '\n';
}

int main() {
	int t; cin >> t;
	while (t--) solve();
}
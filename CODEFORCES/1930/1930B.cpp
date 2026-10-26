#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	int l = 1, r = n;
	vector<int> ans;
	while (true) {
		if (!ans.empty() && ans.back() == l) break;
		ans.push_back(l++);
		if (ans.back() == r) break;
		ans.push_back(r--);
	}
	for (auto i: ans) cout << i << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while (t--) solve();
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n; cin >> n;
	vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
	vector<pair<int, int>> V;
	for (int i = 0; i < n; ++i) {
		V.push_back(make_pair(a[i], i));
	}
	sort(V.begin(), V.end());
	vector<int> ans(n);
	for (int i = 0; i < n; ++i) {
		ans[V[i].second] = n - i;
	}
	for (auto i: ans) cout << i << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}
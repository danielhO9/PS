#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	int n; cin >> n;
	int a[n]; for (int i = 0; i < n; ++i) cin >> a[i];
	map<int, int> M;
	for (auto i: a) ++M[i];
	if (M.size() > 2) {
		cout << "No" << '\n';
		return;
	}
	if (M.size() == 1) {
		cout << "Yes" << '\n';
		return;
	}
	vector<int> V;
	for (auto [i, j]: M) {
		V.push_back(j);
	}
	if (abs(V[0] - V[1]) > 1) {
		cout << "No" << '\n';
		return;
	}
	cout << "Yes" << '\n'; return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}